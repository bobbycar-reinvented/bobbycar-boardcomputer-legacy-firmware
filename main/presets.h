#pragma once

// esp-idf includes
#ifdef FEATURE_NTP
#include <lwip/apps/snmp.h>
#include <esp_sntp.h>
#endif

// 3rdparty lib includes
#include <espchrono.h>

// local includes
#include "settings.h"
#include "ledstripdefines.h"
#include "ledstrip.h"

using namespace std::chrono_literals;

namespace presets {
constexpr Settings::Limits defaultLimits {
    .iMotMax = DEFAULT_IMOTMAX,           // profileSetting
    .iDcMax = DEFAULT_IDCMAX,             // profileSetting
    .nMotMax = DEFAULT_NMOTMAX,           // profileSetting
    .fieldWeakMax = DEFAULT_FIELDWEAKMAX, // profileSetting
    .phaseAdvMax = DEFAULT_FIELDADVMAX    // profileSetting
};

constexpr Settings::Limits kidsLimits {
    .iMotMax = 5,
    .iDcMax = 7,
    .nMotMax = 500,
    .fieldWeakMax = 2,
    .phaseAdvMax = 20
};

constexpr Settings::ControllerHardware defaultControllerHardware {
    .enableFrontLeft = true,  // profileSetting
    .enableFrontRight = true, // profileSetting
    .enableBackLeft = true,   // profileSetting
    .enableBackRight = true,  // profileSetting

    .invertFrontLeft = DEFAULT_INVERTFRONTLEFT,   // profileSetting
    .invertFrontRight = DEFAULT_INVERTFRONTRIGHT, // profileSetting
    .invertBackLeft = DEFAULT_INVERTBACKLEFT,     // profileSetting
    .invertBackRight = DEFAULT_INVERTBACKRIGHT,   // profileSetting
};

constexpr Settings::ControllerHardware mosfetsOffControllerHardware {
    .enableFrontLeft = false,
    .enableFrontRight = false,
    .enableBackLeft = false,
    .enableBackRight = false,

    .invertFrontLeft = DEFAULT_INVERTFRONTLEFT,
    .invertFrontRight = DEFAULT_INVERTFRONTRIGHT,
    .invertBackLeft = DEFAULT_INVERTBACKLEFT,
    .invertBackRight = DEFAULT_INVERTBACKRIGHT,
};

constexpr Settings::ControllerHardware spinnerControllerHardware {
    .enableFrontLeft = true,
    .enableFrontRight = true,
    .enableBackLeft = true,
    .enableBackRight = true,

    .invertFrontLeft = DEFAULT_INVERTFRONTLEFT,
    .invertFrontRight = !DEFAULT_INVERTFRONTRIGHT,
    .invertBackLeft = DEFAULT_INVERTBACKLEFT,
    .invertBackRight = !DEFAULT_INVERTBACKRIGHT,
};

constexpr Settings::DefaultMode defaultDefaultMode {
    .modelMode = UnifiedModelMode::FocTorque, // profileSetting
    .squareGas = true,
    .squareBrems = true,
    .enableSmoothingUp = true,                // profileSetting
    .enableSmoothingDown = true,              // profileSetting
    .enableFieldWeakSmoothingUp = false,      // profileSetting
    .enableFieldWeakSmoothingDown = false,    // profileSetting
    .smoothing = 20,                          // profileSetting
    .frontPercentage = 100,                   // profileSetting
    .backPercentage = 100,                    // profileSetting
    .add_schwelle = 750,                      // profileSetting
    .gas1_wert = 1250,                        // profileSetting
    .gas2_wert = 1250,                        // profileSetting
    .brems1_wert = 250,                       // profileSetting
    .brems2_wert = 750,                       // profileSetting
    .fwSmoothLowerLimit = 800                 // profileSetting
};

constexpr Settings::DefaultMode sinusoidalDefaultMode {
    .modelMode = UnifiedModelMode::Sinusoidal,
    .squareGas = true,
    .squareBrems = true,
    .enableSmoothingUp = true,
    .enableSmoothingDown = true,
    .enableFieldWeakSmoothingUp = false,
    .enableFieldWeakSmoothingDown = false,
    .smoothing = 20,
    .frontPercentage = 100,
    .backPercentage = 100,
    .add_schwelle = 500,
    .gas1_wert = 1250,
    .gas2_wert = 1250,
    .brems1_wert = 150,
    .brems2_wert = 1000,
    .fwSmoothLowerLimit = 800
};

constexpr Settings::TempomatMode defaultTempomatMode {
    .modelMode = UnifiedModelMode::FocSpeed // profileSetting
};

constexpr Settings::LarsmMode defaultLarsmMode {
    .modelMode = UnifiedModelMode::Commutation, // profileSetting
    .mode = LarsmModeMode::Mode4,               // profileSetting
    .iterations = 100                           // profileSetting
};

constexpr Settings::MotortestMode defaultMotortestMode {
    .multiplikator = 2,
    .maxPwm = 400
};

constexpr Settings::Hybrid defaultHybrid {
    .hybridMode = UnifiedModelMode::FocTorque,
    .enable = false,
    .activationLimit = 1000,
    .deactivationLimit = 950,
};

constexpr Settings defaultSettings {
    .limits = defaultLimits,
    .controllerHardware = defaultControllerHardware,
    .defaultMode = defaultDefaultMode,
    .tempomatMode = defaultTempomatMode,
    .larsmMode = defaultLarsmMode,
    .motortestMode = defaultMotortestMode,
    .hybrid = defaultHybrid
};
} // namespace presets
