#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class RecoveryMenu : public BobbyMenuDisplay
{
    using Base = BobbyMenuDisplay;
public:
    RecoveryMenu();

    std::string title() const override;

    void back() override {}

};
} // namespace bobby
