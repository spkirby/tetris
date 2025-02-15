#pragma once
#include "StatusNumber.h"

class StatusPanel
{
public:
    Point position;

    StatusPanel();
    void render(Graphics& graphics);
    void setLevel(int level);
    void setLines(int lines);
    void setScore(int score);

protected:
    StatusNumber level;
    StatusNumber lines;
    StatusNumber score;
};