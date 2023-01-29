#include "otamenu.h"

// 3rdparty lib includes
#include <actioninterface.h>
#include <actions/dummyaction.h>
#include <actions/popscreenaction.h>
#include <actions/pushscreenaction.h>

// local includes
#include "icons/back.h"
#include "icons/back_grey.h"
#include "icons/presets.h"
#include "icons/presets_grey.h"
#include "icons/update.h"
#include "icons/update_grey.h"
#include "screens/selectbuildserverbranch.h"
#include "screens/selectbuildservermenu.h"
#include "screens/selectotabuildmenu.h"
#include "screens/updatedisplay.h"

namespace bobby {

namespace {
constexpr char TEXT_UPDATE[] = "Update";
constexpr char TEXT_UPDATENOW[] = "Update now";
constexpr char TEXT_SELECTBUILD[] = "Select build";
constexpr char TEXT_SELECT_BRANCH[] = "Select Branch";
constexpr char TEXT_SELECTBUILDSERVERMENU[] = "Select Buildserver";
constexpr char TEXT_BACK[] = "Back";
} // namespace

OtaMenu::OtaMenu()
{
    using namespace espgui;
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTBUILD>,             PushScreenAction<SelectBuildMenu>, StaticMenuItemIcon<&bobbyicons::presets, &bobbyicons::presets_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECT_BRANCH>,           PushScreenAction<SelectBuildserverBranchMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_UPDATENOW>,               PushScreenAction<UpdateDisplay>, StaticMenuItemIcon<&bobbyicons::update, &bobbyicons::update_grey>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_SELECTBUILDSERVERMENU>,   PushScreenAction<SelectBuildServerMenu>>>();
    constructMenuItem<makeComponent<MenuItem, StaticText<TEXT_BACK>,                    PopScreenAction, StaticMenuItemIcon<&bobbyicons::back, &bobbyicons::back_grey>>>();
}

std::string OtaMenu::title() const
{
    return TEXT_UPDATE;
}

void OtaMenu::back()
{
    espgui::popScreen();
}
} // namespace bobby
