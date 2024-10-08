#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class LockscreenSettingsMenu : public BobbyMenuDisplay
{
public:
    LockscreenSettingsMenu();

    std::string title() const override;

    void back() override;
};
} // namespace bobby
