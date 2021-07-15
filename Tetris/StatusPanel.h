#pragma once
#include "Entity.h"
#include "StatusNumber.h"

class StatusPanel : public Entity
{
public:
    StatusPanel();
    virtual void render(Graphics& graphics) override;
    void setLevel(int level);
    void setLines(int lines);
    void setScore(int score);

protected:
    StatusNumber level;
    StatusNumber lines;
    StatusNumber score;
};