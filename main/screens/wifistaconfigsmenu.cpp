#include "wifistaconfigsmenu.h"

// 3rdparty lib includes
#include <actions/dummyaction.h>
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <espwifistack.h>
#include <fmt/core.h>
#include <menuitem.h>
#include <screenmanager.h>
#include <strutils.h>

// local includes
#include "icons/back.h"
#include "icons/back_grey.h"
#include "newsettings.h"
#include "wifistaconfigentrymenu.h"

namespace bobby {

using namespace espgui;

namespace {
constexpr char TEXT_BACK[] = "Back";

class WifiStaConfigurationMenuItem : public MenuItem
{
public:
    WifiStaConfigurationMenuItem(int index) : m_index{index} {}

    void triggered() override;
    std::string text() const override;

private:
    const int m_index;
};
} // namespace

WifiStaConfigsMenu::WifiStaConfigsMenu()
{
    for (int i = 0; i < configs.wifi_configs.size(); i++)
        constructMenuItem<WifiStaConfigurationMenuItem>(i);
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string WifiStaConfigsMenu::title() const
{
    return "Configurations";
}

void WifiStaConfigsMenu::back()
{
    popScreen();
}

namespace {

void WifiStaConfigurationMenuItem::triggered()
{
    pushScreen<WifiStaConfigEntryMenu>(m_index);
}

std::string WifiStaConfigurationMenuItem::text() const
{
    const auto &config = configs.wifi_configs[m_index];
    const auto &ssid = config.ssid.value();

    bool connected{};
    if (!ssid.empty() && wifi_stack::get_sta_status() == wifi_stack::WiFiStaStatus::CONNECTED)
        if (const auto &result = wifi_stack::get_sta_ap_info(); result)
            if (cpputils::stringEqualsIgnoreCase(std::string_view{reinterpret_cast<const char*>(result->ssid)}, ssid))
                connected = true;

    return fmt::format("&s{}: &f{}{}",
                       m_index + 1,
                       ssid.empty() ? "&1" : (connected ? "&2" : ""),
                       ssid.empty() ? "<empty>" : ssid);
}

} // namespace
} // namespace bobby
