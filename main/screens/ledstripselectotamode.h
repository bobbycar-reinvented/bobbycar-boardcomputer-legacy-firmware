#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class LedstripOtaAnimationChangeMenu : public BobbyMenuDisplay
{
public:
    LedstripOtaAnimationChangeMenu();

    std::string title() const override;
    void back() override;
};

} // namespace bobby
