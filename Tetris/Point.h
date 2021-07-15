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

    Point operator +(const Point& other);
    Point& operator +=(const Point& other);
    Point operator -(const Point& other);
    Point& operator -=(const Point& other);
};
