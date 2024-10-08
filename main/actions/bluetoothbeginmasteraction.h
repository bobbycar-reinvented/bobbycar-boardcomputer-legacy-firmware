#pragma once

#include "actioninterface.h"
#include "globals.h"
#include "newsettings.h"

using namespace espgui;

namespace {
#ifdef FEATURE_BLUETOOTH
class BluetoothBeginMasterAction : public virtual ActionInterface
{
public:
    void triggered() override
    {
        if (!bluetoothSerial.begin(configs.bluetoothName.value.c_str(), true))
        {
            //Serial.println("Could not begin bluetooth master");
            // TODO: better error handling
        }
    }
};
#endif
}
