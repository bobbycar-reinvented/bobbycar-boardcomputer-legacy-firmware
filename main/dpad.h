#pragma once

// system includes
#include <tuple>

// Arduino includes
#include <esp32-hal-gpio.h>

// 3rdparty lib includes
#include <espchrono.h>
#include <screenmanager.h>

// local includes
#include "types.h"
#include "newsettings.h"
#include "bobbybuttons.h"

namespace {
namespace dpad
{
using State = std::tuple<bool, bool, bool, bool>;

template<pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
class Helper
{
 public:
    void begin();

    State read();
};

template<pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
void Helper<IN1, IN2, IN3, IN4>::begin()
{
  pinMode(IN1, INPUT_PULLUP);
  pinMode(IN2, INPUT_PULLUP);
  pinMode(IN3, INPUT_PULLUP);
  pinMode(IN4, INPUT_PULLUP);
}

template<pin_t IN1, pin_t IN2, pin_t IN3, pin_t IN4>
State Helper<IN1, IN2, IN3, IN4>::read()
{
    const bool result0 = digitalRead(IN1);
    const bool result1 = digitalRead(IN2);
    const bool result2 = digitalRead(IN3);
    const bool result3 = digitalRead(IN4);

    return std::make_tuple(result0, result1, result2, result3);
}

#ifdef FEATURE_DPAD
Helper<PINS_DPAD_UP, PINS_DPAD_DOWN, PINS_DPAD_CONFIRM, PINS_DPAD_BACK> helper;
State lastState;
espchrono::millis_clock::time_point debounceUp, debounceDown, debounceConfirm, debounceBack;

void init()
{
    helper.begin();
}

void update()
{
    const auto state = helper.read();
    const auto now = espchrono::millis_clock::now();

    enum {
        ButtonUp = 0,
        ButtonDown = 1,
        ButtonConfirm = 2,
        ButtonBack = 3
    };

    if (std::get<ButtonUp>(lastState) != std::get<ButtonUp>(state) && now-debounceUp > profileSettings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::upButton(std::get<ButtonUp>(state));
        std::get<ButtonUp>(lastState) = std::get<ButtonUp>(state);
        debounceUp = now;
    }
    if (std::get<ButtonDown>(lastState) != std::get<ButtonDown>(state) && now-debounceDown > profileSettings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::downButton(std::get<ButtonDown>(state));
        std::get<ButtonDown>(lastState) = std::get<ButtonDown>(state);
        debounceDown = now;
    }
    if (std::get<ButtonConfirm>(lastState) != std::get<ButtonConfirm>(state) && now-debounceConfirm > profileSettings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::confirmButton(std::get<ButtonConfirm>(state));
        std::get<ButtonConfirm>(lastState) = std::get<ButtonConfirm>(state);
        debounceConfirm = now;
    }
    if (std::get<ButtonBack>(lastState) != std::get<ButtonBack>(state) && now-debounceBack > profileSettings.boardcomputerHardware.dpadDebounce)
    {
        InputDispatcher::backButton(std::get<ButtonBack>(state));
        std::get<ButtonBack>(lastState) = std::get<ButtonBack>(state);
        debounceBack = now;
    }
}

constexpr const uint8_t BUTTON_COUNT = 4;
#endif
} // namespace dpad
} // namespace
