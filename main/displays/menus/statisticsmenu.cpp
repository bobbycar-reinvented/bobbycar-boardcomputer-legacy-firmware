#include "statisticsmenu.h"

// local includes
#include "mainmenu.h"
#include "actions/dummyaction.h"
#include "actioninterface.h"
#include "fmt/core.h"
#include "utils.h"
#include "icons/time.h"
#include "icons/reboot.h"
#include "icons/update.h"
#include "drivingstatistics.h"

using namespace espgui;

class WhPerKmText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        float avgVoltage = 0;
        for (auto &controller : controllers)
        {
            avgVoltage += controller.getCalibratedVoltage();
        }
        avgVoltage = avgVoltage / controllers.size();

        auto watt = sumCurrent * avgVoltage;
        auto w_per_kmh = watt / avgSpeedKmh;
        return fmt::format("{:.0f} Wh/km", w_per_kmh);
    }
};

class UptimeText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return get_current_uptime_string();
    }
};

class CurrentKilometersText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("Curr: {:.2f}m", drivingStatistics.meters_driven);
    }
};

class TotalKilometersText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("total: {:.1f}km", drivingStatistics.totalMeters / 1000.f );
    }
};

class TotalMetersText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("total: {:.0f}m", drivingStatistics.totalMeters );
    }
};

class CurrentDrivingTimeText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return get_current_driving_time_string();
    }
};

class SavedTotalCentimetersText : public virtual espgui::TextInterface {
    public: std::string text() const override {
        return fmt::format("saved: {}cm", settings.savedStatistics.totalCentimeters );
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

class EfficiencyTextColor : public virtual espgui::ColorInterface {
public:
    int color() const override
    {
        return getEfficiencyClassColor();
    }
};

class SaveKilometersAction : public virtual ActionInterface {
public:
    void triggered() override {
        drivingStatistics.last_cm_written = drivingStatistics.totalMeters * 100;
        settings.savedStatistics.totalCentimeters = drivingStatistics.last_cm_written;
        saveSettings();
    }
};

class ClearCurrentStatsAction : public virtual ActionInterface {
public:
    void triggered() override {
        drivingStatistics.meters_driven = 0.;
        drivingStatistics.currentDrivingTime = {};
        drivingStatistics.wh_used = 0;
        drivingStatistics.batteryWhEstimate = 0;
    }
};

StatisticsMenu::StatisticsMenu()
{
    constructMenuItem<makeComponent<MenuItem, WhPerKmText,                                      DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, UptimeText,                                       DummyAction, StaticMenuItemIcon<&bobbyicons::time>>>();
    constructMenuItem<makeComponent<MenuItem, CurrentKilometersText,                            DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentDrivingTimeText,                           DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TotalKilometersText,                              DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, TotalMetersText,                                  DummyAction>>();
//  constructMenuItem<makeComponent<MenuItem, SavedTotalCentimetersText,                        DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, CurrentWhUsedText,                                DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, AverageWhUsedText,                                DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EfficiencyText, EfficiencyTextColor,              DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, EmptyText,                                        DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSSAVE>,                       SaveKilometersAction, StaticMenuItemIcon<&bobbyicons::update>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_STATSCLEAR>,                      ClearCurrentStatsAction, StaticMenuItemIcon<&bobbyicons::reboot>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                            SwitchScreenAction<MainMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void StatisticsMenu::back()
{
    switchScreen<MainMenu>();
}
