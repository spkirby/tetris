#pragma once
#include "Graphics.h"
#include "Point.h"

class Entity
{
public:
    Point position;

    virtual void render(Graphics& graphics) = 0;
};
