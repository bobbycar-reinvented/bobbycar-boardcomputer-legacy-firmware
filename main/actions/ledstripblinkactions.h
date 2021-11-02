#pragma once

#include "actioninterface.h"
#include "utils.h"
#include "globals.h"
#include "ledstrip.h"
#include "ledstripdefines.h"

using namespace espgui;

#ifdef FEATURE_LEDSTRIP
namespace {
class LedstripAnimationBlinkNoneAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_OVERWRITE_NONE; }
};

class LedstripAnimationBlinkLeftAction : public virtual ActionInterface
{
public:
#ifndef LEDSTRIP_WRONG_DIRECTION
    void triggered() override {
        blinkAnimation = LEDSTRIP_OVERWRITE_BLINKLEFT;
    }
#else
    void triggered() override {
        blinkAnimation = LEDSTRIP_OVERWRITE_BLINKRIGHT;
    }
#endif
};

class LedstripAnimationBlinkRightAction : public virtual ActionInterface
{
public:
#ifndef LEDSTRIP_WRONG_DIRECTION
    void triggered() override {
        blinkAnimation = LEDSTRIP_OVERWRITE_BLINKRIGHT;
    }
#else
    void triggered() override {
        blinkAnimation = LEDSTRIP_OVERWRITE_BLINKLEFT;
    }
#endif
};

class LedstripAnimationBlinkBothAction : public virtual ActionInterface
{
public:
    void triggered() override { blinkAnimation = LEDSTRIP_OVERWRITE_BLINKBOTH; }
};
}
#endif
