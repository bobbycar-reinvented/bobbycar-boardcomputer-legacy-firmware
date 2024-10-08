#pragma once

// local includes
#include "guihelpers/bobbymenudisplay.h"

namespace bobby {

class TaskmanagerMenu : public BobbyMenuDisplay
{
public:
    TaskmanagerMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
