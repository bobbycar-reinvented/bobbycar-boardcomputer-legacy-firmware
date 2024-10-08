#pragma once

// compilation will be broken as there is no config parameter

// local includes
#include "changevaluedisplay.h"
#ifdef FEATURE_BLUETOOTH
#include "changevaluedisplay_bluetoothmode.h"
#endif
#include "guihelpers/bobbymenudisplay.h"
#include "menuitem.h"
#include "actions/dummyaction.h"
#ifdef FEATURE_BLUETOOTH
#include "actions/bluetoothbeginaction.h"
#include "actions/bluetoothbeginmasteraction.h"
#include "actions/bluetoothflushaction.h"
#include "actions/bluetoothendaction.h"
#include "actions/bluetoothdisconnectaction.h"
#endif
#include "actions/switchscreenaction.h"
#include "texthelpers/bluetoothtexthelpers.h"
#include "accessors/settingsaccessors.h"
#include "icons/back.h"

using namespace espgui;
using namespace bluetoothtexthelpers;

namespace {
#ifdef FEATURE_BLUETOOTH
class BluetoothSettingsMenu;

//using AutoBluetoothModeChangeDisplay = makeComponent<
//    ChangeValueDisplay<BluetoothMode>,
//    StaticText<TEXT_AUTOBLUETOOTHMODE>,
//    AutoBluetoothModeAccessor,
//    BackActionInterface<SwitchScreenAction<BluetoothSettingsMenu>>,
//    SwitchScreenAction<BluetoothSettingsMenu>
//>;

class BluetoothSettingsMenu :
    public BobbyMenuDisplay,
    public StaticText<TEXT_BLUETOOTHSETTINGS>,
    public BackActionInterface<SwitchScreenAction<SettingsMenu>>
{
public:
    BluetoothSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, BluetoothAvailableText,                 DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, BluetoothHasClientText,                 DisabledColor, DummyAction>>();
//        constructMenuItem<makeComponent<MenuItem, BluetoothConnectedText,                 DisabledColor, DummyAction>>(); // crashes
        constructMenuItem<makeComponent<MenuItem, BluetoothIsReadyText,                   DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, BluetoothIsReadyMasterText,             DisabledColor, DummyAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGIN>,        BluetoothBeginAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHBEGINMASTER>,  BluetoothBeginMasterAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHFLUSH>,        BluetoothFlushAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHEND>,          BluetoothEndAction>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BLUETOOTHDISCONNECT>,   BluetoothDisconnectAction>>();
//        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_AUTOBLUETOOTHMODE>,     SwitchScreenAction<AutoBluetoothModeChangeDisplay>>>();
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                  SwitchScreenAction<SettingsMenu>, StaticMenuItemIcon<&bobbyicons::back>>>();
    }
};
#endif
} // namespace
