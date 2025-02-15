#pragma once
#include "Point.h"
#include "SDL.h"

class StatusNumber
{
public:
    Point position;

    StatusNumber();
    void render(Graphics& graphics);
    void setValue(unsigned int value);

protected:
    unsigned int value;
    char buffer[8];
};

