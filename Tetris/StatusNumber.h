#pragma once
#include "Entity.h"
#include "Point.h"
#include "SDL.h"

class StatusNumber : public Entity
{
public:
    StatusNumber();
    void setValue(unsigned int value);
    virtual void render(Graphics& graphics) override;

protected:
    unsigned int value;
    bool isDirty;
};

