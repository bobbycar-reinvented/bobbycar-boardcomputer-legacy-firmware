#include "wheelchairmode.h"

#ifdef FEATURE_JOYSTICK
using namespace std::chrono_literals;

namespace modes {
WheelchairMode wheelchairMode;
} // namespace modes

void WheelchairMode::start()
{
    Base::start();
}

// left_right gas
// front_back brems

void WheelchairMode::update()
{
    auto pair = split(profileSettings.defaultMode.modelMode);
    if (!gas || !brems || !raw_gas || !raw_brems)
    {
        start();

        for (bobbycar::protocol::serial::MotorState &motor : motors())
        {
            motor.ctrlTyp = bobbycar::protocol::ControlType::FieldOrientedControl;
            motor.ctrlMod = bobbycar::protocol::ControlMode::OpenMode;
            motor.pwm = 0;
            motor.cruiseCtrlEna = false;
            motor.nCruiseMotTgt = 0;
        }
    }
    else
    {
        const int16_t left_right = configs.gasMin.value() == configs.gasMax.value() ? 0 : *gas;
        const int16_t front_back = configs.bremsMin.value() == configs.bremsMax.value() ? 0 : -*brems;

        float local_gas = 0;
        float local_brems = 0;

        if (front_back > 0)
            local_gas = front_back;
        else if (front_back < 0)
            local_brems = -front_back;

        if (waitForGasLoslass)
        {
            if (local_gas < 50)
                waitForGasLoslass = false;
            else
                local_gas = 0;
        }

        if (waitForBremsLoslass)
        {
            if (local_brems < 50)
                waitForBremsLoslass = false;
            else
                local_brems = 0;
        }

        // ESP_LOGI("BOBBY", "left_right: %i, front_back: %i, local_gas: %.2f, local_brems: %.2f gas: %.2f, brems: %.2f", left_right, front_back, local_gas, local_brems, *gas, *brems);

        auto gas_processed = profileSettings.defaultMode.squareGas ? (local_gas * local_gas) / 1000.f : local_gas;
        auto brems_processed = profileSettings.defaultMode.squareBrems ? (local_brems * local_brems) / 1000 : local_brems;

        const auto now = espchrono::millis_clock::now();

        float pwm;

        if (configs.handbremse.enable.value() && handbremse::stateWish == handbremse::StateWish::brake)
        {
            using namespace handbremse;

            const auto speed = abs(avgSpeedKmh);
            const bool gas_und_brems_ist_null = (gas_processed < 1 && brems_processed < 1);
            if (speed < 2 && gas_und_brems_ist_null)
            {
                angezogen = true;
                stateWish = StateWish::none;
            }
        }

        if (configs.handbremse.enable.value() && configs.handbremse.automatic.value() && !handbremse::angezogen)
        {
            using namespace handbremse;
            const auto speed = abs(avgSpeedKmh);

            if (speed < 1)
            {
                if (!standStillFirstDetected)
                {
                    standStillFirstDetected = now;
                }
            }
            else
                standStillFirstDetected = std::nullopt;

            if (standStillFirstDetected && lastAutoRelease)
                if (espchrono::ago(*standStillFirstDetected) > 100ms * configs.handbremse.triggerTimeout.value() && espchrono::ago(*lastAutoRelease) > 5s )
                {
                    angezogen = true;
                }
        }

        if (handbremse::wishTimer)
        {
            using namespace handbremse;
            if (espchrono::ago(*wishTimer) > 5s)
            {
                stateWish = StateWish::none;
                wishTimer = std::nullopt;
            }
        }

        if (handbremse::angezogen)
        {
            using namespace handbremse;

            standStillFirstDetected = std::nullopt;

            const bool valid = (controllers.front.feedbackValid && controllers.back.feedbackValid);
            const bool gas_oder_brems = (gas_processed > 10 || brems_processed > 10);
            fixCommonParams();

            if (stateWish == StateWish::release)
            {
                lastAutoRelease = now;
                releaseTimer = now;
                stateWish = StateWish::none;
                finishedMotorUpdate = false;
            }

            if (valid && gas_oder_brems)
            {
                if (!releaseTimer)
                {
                    lastAutoRelease = now;
                    releaseTimer = now;
                    finishedMotorUpdate = false;
                }
            }

            if (releaseTimer)
            {
                for (bobbycar::protocol::serial::MotorState &motor : motors())
                {
                    motor.pwm = 0;
                    motor.ctrlTyp = pair.first;
                    motor.ctrlMod = pair.second;
                }

                if (espchrono::ago(*releaseTimer) > 1s || finishedMotorUpdate)
                {
                    releaseTimer = std::nullopt;
                    angezogen = false;
                }
            }
            else
            {
                for (bobbycar::protocol::serial::MotorState &motor : motors())
                {
                    motor.ctrlTyp = bobbycar::protocol::ControlType::FieldOrientedControl;
                    switch (configs.handbremse.mode.value())
                    {
                    case HandbremseMode::MOSFETS_OFF:
                        motor.ctrlMod = bobbycar::protocol::ControlMode::Torque;
                        motor.enable = false;
                        break;
                    case HandbremseMode::OPENMODE:
                        motor.ctrlMod = bobbycar::protocol::ControlMode::OpenMode;
                        break;
                    case HandbremseMode::SPEED_0:
                        motor.ctrlMod = bobbycar::protocol::ControlMode::Speed;
                        break;
                    }
                    motor.pwm = 0;
                    motor.cruiseCtrlEna = false;
                    motor.nCruiseMotTgt = 0;
                }
            }
        }
        else
        {
            pwm = (gas_processed/1000.f*profileSettings.defaultMode.gas1_wert) - (brems_processed/1000.*profileSettings.defaultMode.brems1_wert);

            if (profileSettings.defaultMode.enableSmoothingUp || profileSettings.defaultMode.enableSmoothingDown)
            {
                if (m_lastPwm < pwm && profileSettings.defaultMode.enableSmoothingUp)
                {
                    pwm = std::min(pwm, m_lastPwm + (profileSettings.defaultMode.smoothing * std::chrono::floor<std::chrono::milliseconds>(now - m_lastTime).count() / 100.f));
                }
                else if (m_lastPwm > pwm && profileSettings.defaultMode.enableSmoothingDown)
                {
                    pwm = std::max(pwm, m_lastPwm - (profileSettings.defaultMode.smoothing * std::chrono::floor<std::chrono::milliseconds>(now - m_lastTime).count() / 100.f));
                }
            }

            m_lastPwm = pwm;
            m_lastTime = now;

            float steer = cpputils::mapValueClamped<float>(abs(avgSpeedKmh), 0, 50, profileSettings.wheelchairMode.sensitivity0Kmh, profileSettings.wheelchairMode.sensitivity50Kmh) / 1000.f * left_right;

            for (Controller &controller : controllers)
            {

//                motor.pwm = pwm / 100.f * profileSettings.defaultMode.frontPercentage;

                controller.command.left.ctrlTyp = pair.first;
                controller.command.left.ctrlMod = pair.second;
                controller.command.left.pwm = (pwm - steer);
                controller.command.left.cruiseCtrlEna = false;
                controller.command.left.nCruiseMotTgt = 0;

                controller.command.right.ctrlTyp = pair.first;
                controller.command.right.ctrlMod = pair.second;
                controller.command.right.pwm = (pwm + steer);
                controller.command.right.cruiseCtrlEna = false;
                controller.command.right.nCruiseMotTgt = 0;
            }
        }
    }
}
#endif
