#pragma once

// 3rdparty lib includes

// local includes
#include "displays/bobbymenudisplay.h"
#include "texts.h"

class LarsmModeSettingsMenu :
    public BobbyMenuDisplay,
    public espgui::StaticText<TEXT_LARSMMODESETTINGS>
{
public:
    LarsmModeSettingsMenu();

    void back() override;
};
