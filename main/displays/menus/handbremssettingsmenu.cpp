#include "handbremssettingsmenu.h"

// 3rd party libs
#include <fmt/core.h>
#include <actions/switchscreenaction.h>
#include <changevaluedisplay.h>
#include <icons/back.h>
#include <textwithvaluehelper.h>

// local includes
#include "displays/bobbychangevaluedisplay.h"
#include "accessors/settingsaccessors.h"
#include "changevaluedisplay_handbremsmode.h"
#include "displays/menus/defaultmodesettingsmenu.h"
#include "bobbycheckbox.h"

namespace {
constexpr char TEXT_HANDBREMSE_ENABLE[] = "Enable Handbremse";
constexpr char TEXT_HANDBREMSE_AUTOMATIC[] = "Automatic Handbremse";
constexpr char TEXT_HANDBREMSE_VISUALIZE[] = "Visualize Handbremse";
constexpr char TEXT_HANDBREMSE_MODE[] = "Handbrems Mode";
constexpr char TEXT_HANDBREMSE_TRIGGERTIMEOUT[] = "Handbrems Timeout";
constexpr char TEXT_HANDBREMSE[] = "Handbremse";
constexpr char TEXT_BACK[] = "Back";

using HandBremsTriggerTimeoutChangeValueDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<uint16_t>,
    espgui::StaticText<TEXT_HANDBREMSE_TRIGGERTIMEOUT>,
    HandbremsTimeoutAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<HandbremsSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<HandbremsSettingsMenu>>
>;
using HandBremsModeChangeValueDisplay = espgui::makeComponent<
    BobbyChangeValueDisplay<HandbremseMode>,
    espgui::StaticText<TEXT_HANDBREMSE_MODE>,
    HandbremsModeAccessor,
    espgui::ConfirmActionInterface<espgui::SwitchScreenAction<HandbremsSettingsMenu>>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<HandbremsSettingsMenu>>
>;
class HandBremsModeText : public virtual espgui::TextInterface
{
public:
    std::string text() const override
    {
        return fmt::format("Mode: &2{}", configs.handbremse.mode.valueAsString());
    }
};
}

HandbremsSettingsMenu::HandbremsSettingsMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HANDBREMSE_ENABLE>, BobbyCheckbox, HandbremsEnabledAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HANDBREMSE_AUTOMATIC>, BobbyCheckbox, HandbremsAutomaticAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_HANDBREMSE_VISUALIZE>, BobbyCheckbox, HandbremsVisualizeAccessor>>();
    constructMenuItem<makeComponent<MenuItem, HandBremsModeText,    SwitchScreenAction<HandBremsModeChangeValueDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_HANDBREMSE_TRIGGERTIMEOUT, HandbremsTimeoutAccessor>, SwitchScreenAction<HandBremsTriggerTimeoutChangeValueDisplay>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, SwitchScreenAction<DefaultModeSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

std::string HandbremsSettingsMenu::text() const
{
    return TEXT_HANDBREMSE;
}

void HandbremsSettingsMenu::back()
{
    espgui::switchScreen<DefaultModeSettingsMenu>();
}
