#include <cstdio>
#include <stack>
#include "Enums.h"
#include "Graphics.h"
#include "StatusNumber.h"

StatusNumber::StatusNumber() :
    value(0),
    isDirty(true)
{
}

void StatusNumber::setValue(unsigned int newValue)
{
    if (newValue != value)
    {
        value = newValue;
        isDirty = true;
    }
}

void StatusNumber::render(Graphics& graphics)
{
    if (!isDirty) return;

    unsigned int num = value;

    if (num > 999999)
    {
        num = 999999;
    }

    Point pos = Point(position);
    char buffer[7]; // "999999\0"
    snprintf(buffer, sizeof(buffer), "%u", num);
    
    for (int i = strlen(buffer) - 1; i >= 0; i--)
    {
        int width = graphics.renderDigit(buffer[i] - '0', pos);
        pos.x += (4 + width);
    }

    isDirty = false;
}
