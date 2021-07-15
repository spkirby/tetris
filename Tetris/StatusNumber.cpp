#include <cstdio>
#include <stack>
#include "Enums.h"
#include "Graphics.h"
#include "StatusNumber.h"

StatusNumber::StatusNumber() :
    value(0),
    buffer("0\0")
{
}

void StatusNumber::setValue(unsigned int newValue)
{
    if (newValue != value)
    {
        value = newValue;

        if (newValue > 999999)
        {
            newValue = 999999;
        }

        snprintf(buffer, sizeof(buffer), "%u", newValue);
    }
}

void StatusNumber::render(Graphics& graphics)
{
    Point pos = Point(position);
    
    for (int i = strlen(buffer) - 1; i >= 0; i--)
    {
        int width = graphics.renderDigit(buffer[i] - '0', pos);
        pos.x += (4 + width);
    }
}
