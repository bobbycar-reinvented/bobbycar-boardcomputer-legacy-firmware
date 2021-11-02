#include "lockscreensettingsmenu.h"

// 3rdparty lib includes
#include "menuitem.h"
#include "actions/toggleboolaction.h"
#include "actions/switchscreenaction.h"
#include "icons/back.h"
#include "checkboxicon.h"
#include "changevaluedisplay.h"

// local includes
#include "globals.h"
#include "accessors/settingsaccessors.h"
#include "displays/menus/boardcomputerhardwaresettingsmenu.h"

namespace {
using LockscreenPinDigit0ChangeScreen = espgui::makeComponent<
    espgui::ChangeValueDisplay<int8_t>,
    espgui::StaticText<TEXT_PINDIGIT0>,
    LockscreenPinDigitAccessor<0>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LockscreenSettingsMenu>>,
    espgui::SwitchScreenAction<LockscreenSettingsMenu>
>;

using LockscreenPinDigit1ChangeScreen = espgui::makeComponent<
    espgui::ChangeValueDisplay<int8_t>,
    espgui::StaticText<TEXT_PINDIGIT1>,
    LockscreenPinDigitAccessor<1>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LockscreenSettingsMenu>>,
    espgui::SwitchScreenAction<LockscreenSettingsMenu>
>;

using LockscreenPinDigit2ChangeScreen = espgui::makeComponent<
    espgui::ChangeValueDisplay<int8_t>,
    espgui::StaticText<TEXT_PINDIGIT2>,
    LockscreenPinDigitAccessor<2>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LockscreenSettingsMenu>>,
    espgui::SwitchScreenAction<LockscreenSettingsMenu>
>;

using LockscreenPinDigit3ChangeScreen = espgui::makeComponent<
    espgui::ChangeValueDisplay<int8_t>,
    espgui::StaticText<TEXT_PINDIGIT3>,
    LockscreenPinDigitAccessor<3>,
    espgui::BackActionInterface<espgui::SwitchScreenAction<LockscreenSettingsMenu>>,
    espgui::SwitchScreenAction<LockscreenSettingsMenu>
>;
} // namespace

using namespace espgui;

LockscreenSettingsMenu::LockscreenSettingsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ALLOWPRESETSWITCH>, ToggleBoolAction, CheckboxIcon, LockscreenAllowPresetSwitchAccessor>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_PINDIGIT0, LockscreenPinDigitAccessor<0>>, SwitchScreenAction<LockscreenPinDigit0ChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_PINDIGIT1, LockscreenPinDigitAccessor<1>>, SwitchScreenAction<LockscreenPinDigit1ChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_PINDIGIT2, LockscreenPinDigitAccessor<2>>, SwitchScreenAction<LockscreenPinDigit2ChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_PINDIGIT3, LockscreenPinDigitAccessor<3>>, SwitchScreenAction<LockscreenPinDigit3ChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                                              SwitchScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&espgui::icons::back>>>();
}

void LockscreenSettingsMenu::back()
{
    switchScreen<BoardcomputerHardwareSettingsMenu>();
}
