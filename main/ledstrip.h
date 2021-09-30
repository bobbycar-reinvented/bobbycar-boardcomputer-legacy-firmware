#pragma once

#ifdef FEATURE_LEDSTRIP
// 3rdparty lib includes
#include <FastLED.h>

// local includes
#include "globals.h"
#include "cpputils.h"
#include "espchrono.h"
#include "ledstripdefines.h"

namespace {
std::vector<CRGB> leds;
uint8_t gHue = 0;

int16_t blinkAnimation = LEDSTRIP_ANIMATION_DEFAULT;

void showDefaultLedstrip();

void initLedStrip()
{
    leds.resize(settings.ledstrip.ledsCount);
    FastLED.addLeds<NEOPIXEL, PINS_LEDSTRIP>(&*std::begin(leds), leds.size())
        .setCorrection(TypicalSMD5050);
}

void updateLedStrip()
{
    EVERY_N_MILLISECONDS( 20 ) { gHue++; }

    if (cpputils::is_in(blinkAnimation, LEDSTRIP_ANIMATION_BLINKLEFT, LEDSTRIP_ANIMATION_BLINKRIGHT, LEDSTRIP_ANIMATION_BLINKBOTH))
    {
        std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});

        if (espchrono::millis_clock::now().time_since_epoch() % 750ms < 375ms)
        {
            auto color = CRGB{255, 255, 0};
            const auto center = (std::begin(leds) + (leds.size() / 2) + settings.ledstrip.centerOffset);

            #ifdef LEDSTRIP_WRONG_DIRECTION
                if(blinkAnimation == LEDSTRIP_ANIMATION_BLINKLEFT){
                    blinkAnimation = LEDSTRIP_ANIMATION_BLINKRIGHT;
                } else if(blinkAnimation == LEDSTRIP_ANIMATION_BLINKRIGHT){
                    blinkAnimation = LEDSTRIP_ANIMATION_BLINKLEFT;
                }
            #endif

            if (blinkAnimation != LEDSTRIP_ANIMATION_BLINKLEFT)
                std::fill(center - settings.ledstrip.bigOffset, center - settings.ledstrip.smallOffset, color);
            if (blinkAnimation != LEDSTRIP_ANIMATION_BLINKRIGHT)
                std::fill(center + settings.ledstrip.smallOffset, center + settings.ledstrip.bigOffset, color);
        }
    }
    else
    {
        if (settings.ledstrip.enableBrakeLights)
        {
            float avgPwm{};
            for (const Controller &controller : controllers)
            {
                avgPwm +=
                    controller.command.left.pwm * (controller.invertLeft ? -1 : 1) +
                    controller.command.right.pwm * (controller.invertRight ? -1 : 1);
            }
            avgPwm /= 4;

            if (avgPwm < -1.f)
            {
                auto color = avgSpeedKmh < -0.1f ? CRGB{255, 255, 255} : CRGB{255, 0, 0};

                const auto center = (std::begin(leds) + (leds.size() / 2) + settings.ledstrip.centerOffset);

                std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
                std::fill(center - settings.ledstrip.bigOffset, center - settings.ledstrip.smallOffset, color);
                std::fill(center + settings.ledstrip.smallOffset, center + settings.ledstrip.bigOffset, color);
            }
            else
            {
                showDefaultLedstrip();
            }
        }
        else
        {
            showDefaultLedstrip();
        }
    }

    FastLED.setMaxPowerInVoltsAndMilliamps(5,settings.ledstrip.deziampere * 100);
    FastLED.show();
}

void showDefaultLedstrip()
{
    if (settings.ledstrip.enableLedAnimation)
    {
        fadeToBlackBy(&*std::begin(leds), leds.size(), 20);

        uint8_t dothue = 0;
        for (int i = 0; i < 8; i++)
        {
            leds[beatsin16(i + 7, 0, leds.size())] |= CHSV(dothue, 200, 255);
            dothue += 32;
        }
    }
    else
        std::fill(std::begin(leds), std::end(leds), CRGB{0, 0, 0});
}
} // namespace
#endif
