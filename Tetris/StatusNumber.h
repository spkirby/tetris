#pragma once
#include "Entity.h"
#include "Point.h"
#include "SDL.h"

class StatusNumber : public Entity
{
public:
    StatusNumber();
    virtual void render(Graphics& graphics) override;
    void setValue(unsigned int value);

protected:
    unsigned int value;
    char buffer[7];
};

