#include "ask_calibrate_other_buttons.h"

// 3rdparty lib includes
#include <screenmanager.h>

// local includes
#include "displays/menus/extrabuttoncalibratemenu.h"
#include "displays/setup/final_information.h"
#include "setup.h"
#include "utils.h"

namespace {
constexpr char const askSetupOtherButtonsText[] = "Do you want to setup other\nbuttons?\n(Blinker, Profile Buttons, etc.)\n\nPress LEFT to skip other buttons.\nPress RIGHT to setup buttons.";
} // namespace

void SetupAskCalibrateOtherButtonsDisplay::initScreen()
{
    Base::initScreen();

    drawLargeText(askSetupOtherButtonsText);
}

void SetupAskCalibrateOtherButtonsDisplay::start()
{
    if (m_next_screen)
    {
        espgui::switchScreen<SetupFinalInformationDisplay>();
        return;
    }

    Base::start();

    setup::lock();
}

void SetupAskCalibrateOtherButtonsDisplay::buttonPressed(espgui::Button button)
{
    switch (button)
    {
    case espgui::Left:
        espgui::switchScreen<SetupFinalInformationDisplay>();
        return;
    case espgui::Right:
        m_next_screen = true;
        espgui::pushScreen<ExtraButtonCalibrateMenu>();
        return;
    default:;
    }

    Base::buttonPressed(button);
}

std::string SetupAskCalibrateOtherButtonsDisplay::text() const
{
    return "Other Buttons";
}
