#include "crashmenu.h"

// 3rdparty lib includes
#include <actions/popscreenaction.h>

// local includes
#include "actions/assertaction.h"
#include "actions/dividebyzeroaction.h"
#include "icons/back.h"
#include "icons/back_grey.h"

namespace bobby {

namespace {
constexpr char TEXT_CRASHMENU[] = "Crash Menu";
constexpr char TEXT_CRASH_ASSERT[] = "assert(0)";
constexpr char TEXT_CRASH_DIVZERO[] = "42 / 0";
constexpr char TEXT_BACK[] = "Back";
} // namespace

CrashMenu::CrashMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CRASH_ASSERT>,    AssertAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_CRASH_DIVZERO>,   DivideByZeroAction>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,            PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string CrashMenu::title() const
{
    return TEXT_CRASHMENU;
}

void CrashMenu::back()
{
    espgui::popScreen();
}

} // namespace bobby
