#include "speedinfodisplay.h"

// 3rdparty lib includes
#include <fmt/core.h>
#include <screenmanager.h>

// local includes
#include "displays/batteryinfodisplay.h"
#include "displays/menus/mainmenu.h"
#include "displays/statusdisplay.h"
#include "drivingstatistics.h"

void SpeedInfoDisplay::initScreen()
{
    Base::initScreen();

    m_labelSpeed.start();

    m_dischargingBar.start();
    m_chargingBar.start();

    m_batteryPercentLabel.start();
    m_voltageLabel.start();
    m_distanceLabel.start();
    m_currentConsumptionLabel.start();
}

void SpeedInfoDisplay::redraw()
{
    using namespace espgui;

    Base::redraw();

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextFont(4);

    tft.setTextSize(4);

    m_labelSpeed.redraw(fmt::format(
            std::abs(avgSpeedKmh) < 10 ? "{:.2f}" :
            (std::abs(avgSpeedKmh) < 100 ? "{:.1f}" : "{:.0f}"),
            avgSpeedKmh));

    tft.setTextSize(1);
    m_batteryPercentLabel.redraw(getBatteryPercentageString());

    if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage) {
        auto watt = sumCurrent * *avgVoltage;
        auto wh_per_km = std::abs(avgSpeedKmh) > 0.1 ? watt / std::abs(avgSpeedKmh) : 0;

        m_voltageLabel.redraw(fmt::format("{:.1f} V", avgVoltage.value()));
        m_currentConsumptionLabel.redraw(fmt::format("{:.1f} Wh/km", wh_per_km));
    } else {
        m_voltageLabel.redraw("No voltage");
        m_currentConsumptionLabel.redraw("No comsumption");
    }

    m_distanceLabel.redraw(fmt::format(
            drivingStatistics.meters_driven > 1000 ? "{:.3f} km" :
            (drivingStatistics.meters_driven > 100 ? "{:.1f} m" : "{:.2f} m"),
            drivingStatistics.meters_driven > 1000 ?
                drivingStatistics.meters_driven / 1000 :
                drivingStatistics.meters_driven));

    tft.setTextSize(1);

    m_dischargingBar.redraw(sumCurrent < 0.f ? (-sumCurrent) : 0.f);
    m_chargingBar.redraw(sumCurrent > 0.f ? sumCurrent : 0.f);
}

void SpeedInfoDisplay::buttonPressed(espgui::Button button)
{
    Base::buttonPressed(button);

    switch (button) {
        using espgui::Button;
        case Button::Right:
            espgui::pushScreen<MainMenu>();
            break;
        case Button::Up:
            espgui::switchScreen<BatteryInfoDisplay>();
            break;
        case Button::Down:
#ifdef FEATURE_BMS
            espgui::switchScreen<BmsDisplay>();
#else
            espgui::switchScreen<StatusDisplay>();
#endif
            break;
        default:;
    }
}
