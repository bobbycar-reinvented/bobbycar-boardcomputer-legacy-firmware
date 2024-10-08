#include "bmsmenu.h"

#if defined(FEATURE_BLUETOOTH) && defined(FEATURE_BMS)
// local includes
#include "menuitem.h"
#include "actions/bluetoothconnectbmsaction.h"
#include "actions/bluetoothdisconnectaction.h"
#include "actions/dummyaction.h"
#include "actions/bmsturnonchargeaction.h"
#include "actions/bmsturnoffchargeaction.h"
#include "actions/bmsturnondischargeaction.h"
#include "actions/bmsturnoffdischargeaction.h"
#include "actions/popscreenaction.h"
#include "bluetoothtexthelpers.h"
#include "icons/back.h"

using namespace espgui;
using namespace bluetoothtexthelpers;

BmsMenu::BmsMenu()
{
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CONNECTBMS>,       BluetoothConnectBmsAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_DISCONNECTBMS>,    BluetoothDisconnectAction>>();
    constructMenuItem<makeComponent<MenuItem, BluetoothHasClientText,            DisabledColor, DummyAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TURNONCHARGE>,     BmsTurnOnChargeAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TURNOFFCHARGE>,    BmsTurnOffChargeAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TURNONDISCHARGE>,  BmsTurnOnDischargeAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_TURNOFFDISCHARGE>, BmsTurnOffDischargeAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,             PopScreenAction, StaticMenuItemIcon<&bobbyicons::back>>>();
}

void BmsMenu::back()
{
    popSreen();
}
#endif
