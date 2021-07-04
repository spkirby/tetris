#include "Point.h"

Point::Point() :
    x(0),
    y(0)
{
}

Point::Point(int x, int y) :
    x(x),
    y(y)
{
}

Point Point::operator +(Point& other)
{
    return Point(x + other.x, y + other.y);
}

Point Point::operator -(Point& other)
{
    return Point(x - other.x, y - other.y);
}