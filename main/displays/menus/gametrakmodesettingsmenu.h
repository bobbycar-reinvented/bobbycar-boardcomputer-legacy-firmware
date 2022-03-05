#pragma once

// local includes
#include "displays/bobbymenudisplay.h"
#include "utils.h"
#include "menuitem.h"
#include "actions/popscreenaction.h"
#include "icons/back.h"

namespace {
#ifdef FEATURE_GAMETRAK
class ContainerModeSettingsMenu :
    public BobbyMenuDisplay,
    public BackActionInterface<SwitchScreenAction<ModesSettingsMenu>>
{
public:
    ContainerModeSettingsMenu()
    {
        constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>, PopScreenAction, StaticMenuItemIcon<&espgui::icons::back>>>();
    }

    std::string text() const override
    {
        return TEXT_GAMETRAKMODESETTINGS;
    }
};
#endif
} // namespace
