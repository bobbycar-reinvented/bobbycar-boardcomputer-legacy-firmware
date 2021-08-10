#pragma once

// system includes
#include <array>
#include <string>

// 3rdparty lib includes
#ifdef FEATURE_OTA
#include <espasyncota.h>
#endif
#include <fmt/core.h>

// local includes
#include "display.h"
#include "actions/switchscreenaction.h"
#include "globals.h"
#include "texts.h"
#include "widgets/label.h"
#include "widgets/progressbar.h"
#include "modes/ignoreinputmode.h"

namespace {
class StatusDisplay;
}

namespace {
#ifdef FEATURE_OTA
class UpdateDisplay : public Display, public DummyBack
{
public:
    UpdateDisplay(const std::string &title);
    UpdateDisplay(std::string &&title);

    void start() override;
    void initScreen() override;
    void redraw() override;
    void confirm() override;

public:
    bool m_finished;
    unsigned int m_progress;
    unsigned int m_total;

private:
    const std::string m_title;

    Label m_progressLabel{20, 150};

    ProgressBar m_progressBar{20, 200, 200, 10, 0, 100};
};

UpdateDisplay::UpdateDisplay(const std::string &title) :
    m_title{title}
{}

UpdateDisplay::UpdateDisplay(std::string &&title) :
    m_title{std::move(title)}
{}

void UpdateDisplay::start()
{
    m_finished = false;
    m_progress = 0;
    m_total = 1;
}

void UpdateDisplay::initScreen()
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextFont(4);
    tft.setTextColor(TFT_YELLOW);

    tft.drawString(m_title.c_str(), 5, 5, 4);

    tft.fillRect(0, 34, tft.width(), 3, TFT_WHITE);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString("Progress:", 20, 125);
    m_progressLabel.start();

    m_progressBar.start();
}

void UpdateDisplay::redraw()
{
    m_progressLabel.redraw(fmt::format("{}/{}", m_progress, m_total));

    m_progressBar.redraw(float(m_progress) / m_total * 100.f);
}

void UpdateDisplay::confirm()
{
    if (m_finished)
        switchScreen<StatusDisplay>();
}
#endif
}
