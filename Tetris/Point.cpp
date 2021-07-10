#include "Point.h"
#include "Enums.h"

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

Point::Point(Direction direction) :
    x(0),
    y(0)
{
    switch (direction)
    {
    case Direction::Up:
        y = -1;
        break;
    case Direction::Down:
        y = 1;
        break;
    case Direction::Left:
        x = -1;
        break;
    case Direction::Right:
        x = 1;
        break;
    }
}

Point Point::operator +(Point& other)
{
    return Point(x + other.x, y + other.y);
}

Point Point::operator -(Point& other)
{
    return Point(x - other.x, y - other.y);
}
