#pragma once
#include "Entity.h"
#include "StatusNumber.h"

class StatusPanel : public Entity
{
public:
    StatusPanel();
    void setLines(int lines);
    void setLevel(int level);
    void setScore(int score);
    virtual void render(Graphics& graphics) override;

protected:
    StatusNumber lines;
    StatusNumber level;
    StatusNumber score;
};