#pragma once
#include "Entity.h"

class StatusPanel : public Entity
{
public:
    int lines;
    int level;
    int score;

    StatusPanel();
    virtual void render(Graphics& graphics);
};