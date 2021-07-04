#pragma once

class Point
{
public:
    int x;
    int y;

    Point();
    Point(int x, int y);

    Point operator +(Point& other);
    Point operator -(Point& other);
};
