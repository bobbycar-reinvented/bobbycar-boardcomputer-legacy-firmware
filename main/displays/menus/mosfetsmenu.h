#pragma once

#ifdef FEATURE_MOSFETS
#include "menudisplay.h"
#include "accessorinterface.h"
#include "texts.h"
#include "types.h"

template<pin_t PIN>
class GPIOAccessor : public virtual espgui::AccessorInterface<bool>
{
public:
    bool getValue() const override { return digitalRead(PIN); }
    void setValue(bool value) override { digitalWrite(PIN, value ? HIGH : LOW); }
};

using Mosfet0Accessor = GPIOAccessor<PINS_MOSFET0>;
using Mosfet1Accessor = GPIOAccessor<PINS_MOSFET1>;
using Mosfet2Accessor = GPIOAccessor<PINS_MOSFET2>;

class MosfetsMenu :
    public espgui::MenuDisplay,
    public espgui::StaticText<TEXT_MOSFETS>
{
public:
    MosfetsMenu();
    void back() override;
};
#endif
