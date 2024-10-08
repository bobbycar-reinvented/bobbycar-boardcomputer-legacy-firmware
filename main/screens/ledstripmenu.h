#pragma once

// local includes
#include "guihelpers/menudisplaywithtime.h"

namespace bobby {

class LedstripMenu : public bobby::MenuDisplayWithTime
{
public:
    LedstripMenu();

    std::string title() const override;

    void back() override;
};

} // namespace bobby
