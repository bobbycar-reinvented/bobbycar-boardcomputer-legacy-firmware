#include "settingsmenu.h"

// 3rdparty lib includes
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>
#include <changevaluedisplay_string.h>
#include <menuitem.h>
#include <textwithvaluehelper.h>

// local includes
#include "accessors/settingsaccessors.h"
#include "globals.h"
#include "guihelpers/bobbychangevaluedisplay.h"
#include "guihelpers/bobbycheckbox.h"
#include "icons/back.h"
#include "icons/back_grey.h"
#include "icons/bluetooth.h"
#include "icons/bluetooth_grey.h"
#include "icons/buzzer.h"
#include "icons/buzzer_grey.h"
#include "icons/demos.h"
#include "icons/demos_grey.h"
#include "icons/git.h"
#include "icons/git_grey.h"
#include "icons/hardware.h"
#include "icons/hardware_grey.h"
#include "icons/info.h"
#include "icons/info_grey.h"
#include "icons/time.h"
#include "icons/time_grey.h"
#include "icons/update.h"
#include "icons/update_grey.h"
#include "icons/wifi.h"
#include "icons/wifi_grey.h"
#include "screens.h"
#include "screens/aboutmenu.h"
#include "screens/blesettingsmenu.h"
#include "screens/bluetoothsettingsmenu.h"
#include "screens/boardcomputerhardwaresettingsmenu.h"
#include "screens/buzzermenu.h"
#include "screens/cloudsettingsmenu.h"
#include "screens/controllerhardwaresettingsmenu.h"
#include "screens/crashmenu.h"
#include "screens/espnowmenu.h"
#include "screens/featureflagsmenu.h"
#include "screens/gitmenu.h"
#include "screens/limitssettingsmenu.h"
#include "screens/modessettingsmenu.h"
#include "screens/networksettingsmenu.h"
#include "screens/selectbuildservermenu.h"
#include "screens/timesettingsmenu.h"
#include "screens/typesafeenumchangemenu.h"
#include "screens/udpcloudsettingsmenu.h"

namespace bobby {

namespace {
constexpr char TEXT_SETTINGS[] = "Settings";
constexpr char TEXT_BACKLIGHT[] = "Backlight";
constexpr char TEXT_LIMITSSETTINGS[] = "Limits settings";
constexpr char TEXT_NETWORKSETTINGS[] = "Network settings";
constexpr char TEXT_ESPNOW[] = "ESPNOW settings";
constexpr char TEXT_BLUETOOTHSETTINGS[] = "Bluetooth settings";
constexpr char TEXT_BLESETTINGS[] = "BLE settings";
constexpr char TEXT_CLOUDSETTINGS[] = "Cloud settings";
constexpr char TEXT_UDPCLOUDSETTINGS[] = "UDP Cloud settings";
constexpr char TEXT_SELECTBUILDSERVERMENU[] = "Select Buildserver";
constexpr char TEXT_TIME[] = "Time";
constexpr char TEXT_MODESSETTINGS[] = "Modes settings";
constexpr char TEXT_CONTROLLERHARDWARESETTINGS[] = "Controller H/W settings";
constexpr char TEXT_BOARDCOMPUTERHARDWARESETTINGS[] = "Boardcomputer H/W settings";
constexpr char TEXT_FEATUREFLAGS[] = "Feature flags";
constexpr char TEXT_USERNAME[] = "Username"; // ota-name
constexpr char TEXT_ANHAENGER_ID[] = "Anhaenger ID";
constexpr char TEXT_SELECT_DEFAULT_STATUSDISPLAY[] = "Select default display";
constexpr char TEXT_AUTOCONNECTBMS[] = "Auto connect BMS";
constexpr char TEXT_BUZZER[] = "Buzzer";
constexpr char TEXT_FRONTLED[] = "Front LED";
constexpr char TEXT_BACKLED[] = "Back LED";
constexpr char TEXT_CRASHMENU[] = "Crash Menu";
constexpr char TEXT_ABOUT[] = "About";
constexpr char TEXT_GIT[] = "Git";
constexpr char TEXT_BACK[] = "Back";

#ifdef FEATURE_LEDBACKLIGHT
struct BacklightAccessor : public virtual espgui::AccessorInterface<bool>
{
    bool getValue() const override { return !display::backlightDisabled(); }
    setter_result_t setValue(bool value) override
    {
        display::disableBacklight(!value);
        return {};
    }
};
#endif

struct FrontLedAccessor : public espgui::RefAccessor<bool> { bool &getRef() const override { return controllers.front.command.led; } };
struct BackLedAccessor : public espgui::RefAccessor<bool> { bool &getRef() const override { return controllers.back.command.led; } };

using AnhaengerIdChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<uint16_t>,
    espgui::StaticTitle<TEXT_ANHAENGER_ID>,
    AnhaengerIdAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;

using UsernameChangeScreen = espgui::makeComponent<
    BobbyChangeValueDisplay<std::string>,
    espgui::StaticTitle<TEXT_USERNAME>,
    UsernameAccessor,
    espgui::ConfirmActionInterface<espgui::PopScreenAction>,
    espgui::BackActionInterface<espgui::PopScreenAction>
>;
} // namespace

using namespace espgui;

SettingsMenu::SettingsMenu()
{
#ifdef FEATURE_LEDBACKLIGHT
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACKLIGHT>,                     BobbyCheckbox, BacklightAccessor>>();
#endif
    if (!simplified)
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_LIMITSSETTINGS>,            PushScreenAction<LimitsSettingsMenu>>>();

    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_NETWORKSETTINGS>,               PushScreenAction<NetworkSettingsMenu>, StaticMenuItemIcon<&bobbyicons::wifi, &bobbyicons::wifi_grey>>>();
    if (configs.feature.esp_now.isEnabled.value())
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ESPNOW>,                    PushScreenAction<EspNowMenu>, StaticMenuItemIcon<&bobbyicons::wifi, &bobbyicons::wifi_grey>>>();
#ifdef FEATURE_BLUETOOTH
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHSETTINGS>,             PushScreenAction<BluetoothSettingsMenu>, StaticMenuItemIcon<&bobbyicons::bluetooth>>>();
#endif
    if (configs.feature.ble.isEnabled.value())
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLESETTINGS>,               PushScreenAction<BleSettingsMenu>, StaticMenuItemIcon<&bobbyicons::bluetooth, &bobbyicons::bluetooth_grey>>>();
    if (configs.feature.cloud.isEnabled.value())
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CLOUDSETTINGS>,             PushScreenAction<CloudSettingsMenu>>>();
    if (configs.feature.udpcloud.isEnabled.value())
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UDPCLOUDSETTINGS>,          PushScreenAction<UdpCloudSettingsMenu>>>();
    if (configs.feature.ota.isEnabled.value())
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTBUILDSERVERMENU>,     PushScreenAction<SelectBuildServerMenu>, StaticMenuItemIcon<&bobbyicons::update, &bobbyicons::update_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TIME>,                          PushScreenAction<TimeSettingsMenu>, StaticMenuItemIcon<&bobbyicons::time, &bobbyicons::time_grey>>>();
    if (!simplified)
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_MODESSETTINGS>,              PushScreenAction<ModesSettingsMenu>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CONTROLLERHARDWARESETTINGS>, PushScreenAction<ControllerHardwareSettingsMenu>, StaticMenuItemIcon<&bobbyicons::hardware, &bobbyicons::hardware_grey>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BOARDCOMPUTERHARDWARESETTINGS>, PushScreenAction<BoardcomputerHardwareSettingsMenu>, StaticMenuItemIcon<&bobbyicons::hardware, &bobbyicons::hardware_grey>>>();
    }
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FEATUREFLAGS>,                  PushScreenAction<FeatureFlagsMenu>, StaticMenuItemIcon<&bobbyicons::demos, &bobbyicons::demos_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_USERNAME>,                      PushScreenAction<UsernameChangeScreen>>>();
    constructMenuItem<makeComponent<MenuItem, TextWithValueHelper<TEXT_ANHAENGER_ID, AnhaengerIdAccessor>, PushScreenAction<AnhaengerIdChangeScreen>>>();
    constructMenuItem<PushScreenTypeSafeChangeMenuItem<DefaultStatusDisplay, TEXT_SELECT_DEFAULT_STATUSDISPLAY>>(&configs.defaultStatusDisplay);
//#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
//    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_AUTOCONNECTBMS>,                BobbyCheckbox, AutoConnectBmsAccessor>>();
//#endif
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BUZZER>,                        PushScreenAction<BuzzerMenu>, StaticMenuItemIcon<&bobbyicons::buzzer, &bobbyicons::buzzer_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_FRONTLED>,                      BobbyCheckbox, FrontLedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACKLED>,                       BobbyCheckbox, BackLedAccessor>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CRASHMENU>,                     PushScreenAction<CrashMenu>,  StaticMenuItemIcon<&bobbyicons::demos, &bobbyicons::demos_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_ABOUT>,                         PushScreenAction<AboutMenu>, StaticMenuItemIcon<&bobbyicons::info, &bobbyicons::info_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_GIT>,                           PushScreenAction<GitMenu>, StaticMenuItemIcon<&bobbyicons::git, &bobbyicons::git_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                          PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string SettingsMenu::title() const
{
    return TEXT_SETTINGS;
}

void SettingsMenu::back()
{
    popScreen();
}
} // namespace bobby
