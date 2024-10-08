#include "cloudstats.h"

// 3rdparty lib includes
#include <ArduinoJson.h>
#include <delayedconstruction.h>
#include <espchrono.h>

// local includes
#include "battery.h"
#include "drivingstatistics.h"
#include "globals.h"
#include "newsettings.h"
#include "taskmanager.h"
#include "utils.h"

namespace bobby::cloudstats {
using namespace std::chrono_literals;

namespace {
uint8_t packageType{0}; // cycle through packages.
cpputils::DelayedConstruction<StaticJsonDocument<512>> jsonDoc;

bool _udpNeedsConstruction{false};
bool _espnowNeedsConstruction{false};
} // namespace

void udpNeedsConstruction(bool needsConstruction)
{
    _udpNeedsConstruction = needsConstruction;
    updateDependencies();
}

void espnowNeedsConstruction(bool needsConstruction)
{
    _espnowNeedsConstruction = needsConstruction;
    updateDependencies();
}

void updateDependencies()
{
    if (_udpNeedsConstruction || _espnowNeedsConstruction)
    {
        if (!jsonDoc)
            jsonDoc.construct();
    }
    else
    {
        if (jsonDoc)
            jsonDoc.destruct();
    }
}

std::optional<std::string> buildCloudJson()
{
    if (!jsonDoc)
        return std::nullopt;

    auto &doc = *jsonDoc;

    doc.clear();

    switch (++packageType)
    {
    default:
        packageType = 0;
        [[fallthrough]];
    case 0:
    {
        const auto uptime = espchrono::millis_clock::now().time_since_epoch() / 1ms;
        doc["upt"] = uptime;
        doc["loc"] = isLocked;
        doc["mdr"] = drivingStatistics.meters_driven;
        doc["mdt"] = drivingStatistics.totalMeters;
        doc["cdt"] = drivingStatistics.currentDrivingTime / 1ms;
        doc["sha"] = GIT_REV;
        doc["brn"] = GIT_BRANCH;
        doc["idf"] = esp_get_idf_version();
        doc["dir"] = GIT_DIRTY;

        if (const auto wifi_sta_info = getWifiStaInfo(); wifi_sta_info)
        {
            doc["wif"] = (*wifi_sta_info).ssid;
            doc["rssi"] = (*wifi_sta_info).rssi;
        }
        else
        {
            doc["wif"] = nullptr;
            doc["rssi"] = nullptr;
        }
        break;
    }
    case 1:
    case 4:
    {
        if (gas)
            doc["pcg"] = *gas; // poti calculated gas
        if (raw_gas)
            doc["prg"] = *raw_gas; // poti raw gas
        if (brems)
            doc["pcb"] = *brems; // poti calculated brems
        if (raw_brems)
            doc["prb"] = *raw_brems; // poti raw brems

        if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
        {
            doc["bap"] = battery::getBatteryPercentage(*avgVoltage, configs.battery.cellType.value());
            doc["bav"] = *avgVoltage; // battery voltage
            doc["pwr"] = sumCurrent * *avgVoltage; // total watt
        }
        doc["whl"] = battery::getRemainingWattHours(); // watt hours left
        doc["kml"] = battery::getRemainingWattHours() / configs.battery.watthoursPerKilometer.value(); // calculated kilometers left
        doc["ekm"] = getEstimatedKmLeft(); // kilometers left live calculation
        doc["acl"] = avgAccel; // average acceleration
        doc["cur"] = sumCurrent; // total current
        break;
    }
    case 2:
    case 5:
    case 7:
    {
        const auto &controller = controllers.front;
        if (controller.feedbackValid)
        {
            doc["fbv"] = controller.getCalibratedVoltage();

            // Amperes
            doc["fla"] = fixCurrent(controller.feedback.left.dcLink);
            doc["fra"] = fixCurrent(controller.feedback.right.dcLink);

            // Temperature
            doc["fbt"] = fixBoardTemp(controller.feedback.boardTemp);

            // Errors
            doc["fle"] = controller.feedback.left.error;
            doc["fre"] = controller.feedback.right.error;

            // Speed
            doc["fls"] = convertToKmh(controller.feedback.left.speed) * (controller.invertLeft ? -1.f : 1.f);
            doc["frs"] = convertToKmh(controller.feedback.right.speed) * (controller.invertRight ? -1.f : 1.f);
        }
        else
        {
            return std::nullopt;
        }
        break;
    }
    case 3:
    case 6:
    case 8:
    {
        const auto &controller = controllers.back;
        if (controller.feedbackValid)
        {
            doc["bbv"] = controller.getCalibratedVoltage();

            // Amperes
            doc["bla"] = fixCurrent(controller.feedback.left.dcLink);
            doc["bra"] = fixCurrent(controller.feedback.right.dcLink);

            // Temperature
            doc["bbt"] = fixBoardTemp(controller.feedback.boardTemp);

            // Errors
            doc["ble"] = controller.feedback.left.error;
            doc["bre"] = controller.feedback.right.error;

            // Speed
            doc["bls"] = convertToKmh(controller.feedback.left.speed) * (controller.invertLeft ? -1.f : 1.f);
            doc["brs"] = convertToKmh(controller.feedback.right.speed) * (controller.invertRight ? -1.f : 1.f);
        }
        else
        {
            return std::nullopt;
        }
        break;
    }
    }

    // if empty, return empty string
    if (doc.isNull())
    {
        return std::nullopt;
    }

    doc["__t"] = configs.udpCloudSettings.udpToken.value();
    doc["per"] = drivingModeTask.callCount();

    std::string buf;
    serializeJson(doc, buf);
    return buf;
}
}
