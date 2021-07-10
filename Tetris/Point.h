#pragma once
#include "Enums.h"

class Point
{
public:
    int x;
    int y;

    Point();
    Point(int x, int y);
    Point(Direction direction);

    Point operator +(Point& other);
    Point operator -(Point& other);
};
