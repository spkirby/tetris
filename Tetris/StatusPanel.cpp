#include "Graphics.h"
#include "StatusPanel.h"

StatusPanel::StatusPanel() :
    level(1),
    lines(0),
    score(0)
{
}

void StatusPanel::render(Graphics& graphics)
{
    graphics.draw(IMAGE_LOGO, position + Point(482, 192));

    graphics.draw(IMAGE_STATUS_NEXT, position);

    graphics.draw(IMAGE_STATUS_LINES, position + Point(0, 200));
    graphics.drawNumber(lines, position + Point(0, 250));

    graphics.draw(IMAGE_STATUS_LEVEL, position + Point(0, 350));
    graphics.drawNumber(level, position + Point(0, 400));

    graphics.draw(IMAGE_STATUS_SCORE, 0, 500);
    graphics.drawNumber(score, position + Point(0, 550));
}
