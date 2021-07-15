#include "Graphics.h"
#include "StatusPanel.h"

StatusPanel::StatusPanel()
{
}

void StatusPanel::setLines(int lines)
{
    this->lines.setValue(lines);
}

void StatusPanel::setLevel(int level)
{
    this->level.setValue(level);
}

void StatusPanel::setScore(int score)
{
    this->score.setValue(score);
}

void StatusPanel::render(Graphics& graphics)
{
    graphics.renderImage(ImageId::StatusNext, position);

    graphics.renderImage(ImageId::StatusLines, position + Point(0, 200));
    lines.position = position + Point(0, 250);
    lines.render(graphics);

    graphics.renderImage(ImageId::StatusLevel, position + Point(0, 350));
    level.position = position + Point(0, 400);
    level.render(graphics);

    graphics.renderImage(ImageId::StatusScore, position + Point(0, 500));
    score.position = position + Point(0, 550);
    score.render(graphics);
}
