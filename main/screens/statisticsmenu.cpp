#include "statisticsmenu.h"

// 3rdparty lib includes
#include <actioninterface.h>
#include <actions/dummyaction.h>
#include <actions/popscreenaction.h>
#include <fmt/core.h>
#include <menuitem.h>

// local includes
#include "drivingstatistics.h"
#include "icons/back.h"
#include "icons/back_grey.h"
#include "icons/reboot.h"
#include "icons/reboot_grey.h"
#include "icons/time.h"
#include "icons/time_grey.h"
#include "icons/update.h"
#include "icons/update_grey.h"
#include "utils.h"

namespace bobby {

namespace {
constexpr char TEXT_STATISTICSMENU[] = "Statistics";
constexpr char TEXT_STATSSAVE[] = "Save kilometers";
constexpr char TEXT_STATSCLEAR[] = "Clear current km";
constexpr char TEXT_BACK[] = "Back";

class WhPerKmText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        if (const auto avgVoltage = controllers.getAvgVoltage(); avgVoltage)
        {
            auto watt = sumCurrent * *avgVoltage;
            auto w_per_kmh = watt / std::abs(avgSpeedKmh);
            return fmt::format("{:.0f} Wh/km", w_per_kmh);
        }
        return "No Battery";
    }
};

class UptimeText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        using namespace std::chrono_literals;
        const auto uptime = espchrono::millis_clock::now().time_since_epoch();
        auto converted = date::make_time(uptime);
        auto msecs = uptime
                     - converted.hours()
                     - converted.minutes()
                     - converted.seconds();
        return fmt::format("Up: {:02d}:{:02d}:{:02d}&s&7.{:01d}",
                           converted.hours().count(),
                           converted.minutes().count(),
                           converted.seconds().count(),
                           msecs / 1ms);
    }
};

class CurrentKilometersText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("Curr: {:.2f}m", drivingStatistics.meters_driven);
    }
};

class TotalKilometersText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("total: {:.1f}km", drivingStatistics.totalMeters / 1000.f);
    }
};

class TotalMetersText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("total: {:.0f}m", drivingStatistics.totalMeters);
    }
};

class CurrentDrivingTimeText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        auto converted = date::make_time(drivingStatistics.currentDrivingTime);
        auto msecs = drivingStatistics.currentDrivingTime
                     - converted.hours()
                     - converted.minutes()
                     - converted.seconds();
        return fmt::format("Drive: {:02d}:{:02d}:{:02d}&s&7.{:02d}",
                           converted.hours().count(),
                           converted.minutes().count(),
                           converted.seconds().count(),
                           msecs.count());
    }
};

class SavedTotalCentimetersText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("saved: {}cm", configs.savedStatistics.totalCentimeters.value() );
    }
};

class CurrentWhUsedText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("Curr: {:.2f}Wh", drivingStatistics.wh_used );
    }
};

class AverageWhUsedText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("Avg: {:.1f}Wh/km", drivingStatistics.wh_used / (drivingStatistics.meters_driven / 1000.f) );
    }
};

class EfficiencyText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("Efficiency: {}", getEfficiencyClassString());
    }
};

class AverageSpeedKmhOverTime : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("Avg speed: {:.1f} km/h", getAvgKmh());
    }
};

class EstimatedKmLeft : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("est km:{}", getRemainingEstimateRangeString());
    }
};

class EfficiencyTextColor : public virtual espgui::ColorInterface {
public:
    int color() const override
    {
        return getEfficiencyClassColor();
    }
};

class SaveKilometersAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        drivingStatistics.last_cm_written = drivingStatistics.totalMeters * 100;
        configs.write_config(configs.savedStatistics.totalCentimeters, drivingStatistics.last_cm_written);
    }
};

class ClearCurrentStatsAction : public virtual espgui::ActionInterface
{
public:
    void triggered() override
    {
        drivingStatistics.meters_driven = 0.f;
        drivingStatistics.currentDrivingTime = {};
        drivingStatistics.wh_used = 0.f;
        drivingStatistics.batteryWhEstimate = 0.f;
    }
};
} // namespace

StatisticsMenu::StatisticsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, WhPerKmText,                         DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, UptimeText,                          DummyAction, StaticMenuItemIcon<&bobbyicons::time, &bobbyicons::time_grey>>>();
    constructMenuItem<makeComponent<MenuItem, CurrentKilometersText,               DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentDrivingTimeText,              DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TotalKilometersText,                 DummyAction>>();
//  constructMenuItem<makeComponent<MenuItem, SavedTotalCentimetersText,           DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentWhUsedText,                   DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, AverageWhUsedText,                   DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, AverageSpeedKmhOverTime,             DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EstimatedKmLeft,                     DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EfficiencyText, EfficiencyTextColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TotalMetersText,                     DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EmptyText,                           DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSSAVE>,          SaveKilometersAction, StaticMenuItemIcon<&bobbyicons::update, &bobbyicons::update_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSCLEAR>,         ClearCurrentStatsAction, StaticMenuItemIcon<&bobbyicons::reboot, &bobbyicons::reboot_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,               PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string StatisticsMenu::title() const
{
    return TEXT_STATISTICSMENU;
}

void StatisticsMenu::back()
{
    espgui::popScreen();
}
} // namespace bobby
