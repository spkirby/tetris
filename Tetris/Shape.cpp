#include "Enums.h"
#include "Graphics.h"
#include "PlayField.h"
#include "Point.h"
#include "Shape.h"
#include <cstdio>
#include <cstdlib>

const int Shape::shapes[NUM_OF_SHAPES][4][4][4] =
{
    // I
    {
        { // 0
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 }
        },
        { // 90
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 1, 1, 1, 1 },
            { 0, 0, 0, 0 }
        },
        { // 180
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 },
            { 0, 0, 1, 0 }
        },
        { // 270
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 },
            { 1, 1, 1, 1 },
            { 0, 0, 0, 0 }
        }
    },

    // J
    {
        { // 0
            { 0, 0, 2, 0 },
            { 0, 0, 2, 0 },
            { 0, 2, 2, 0 },
            { 0, 0, 0, 0 }
        },
        { // 90
            { 0, 2, 0, 0 },
            { 0, 2, 2, 2 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        { // 180
            { 0, 0, 2, 2 },
            { 0, 0, 2, 0 },
            { 0, 0, 2, 0 },
            { 0, 0, 0, 0 }
        },
        { // 270
            { 0, 0, 0, 0 },
            { 0, 2, 2, 2 },
            { 0, 0, 0, 2 },
            { 0, 0, 0, 0 }
        }
    },

    // L
    {
        { // 0
            { 0, 3, 0, 0 },
            { 0, 3, 0, 0 },
            { 0, 3, 3, 0 },
            { 0, 0, 0, 0 }
        },
        { // 90
            { 0, 0, 0, 0 },
            { 3, 3, 3, 0 },
            { 3, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        { // 180
            { 3, 3, 0, 0 },
            { 0, 3, 0, 0 },
            { 0, 3, 0, 0 },
            { 0, 0, 0, 0 }
        },
        { // 270
            { 0, 0, 3, 0 },
            { 3, 3, 3, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        }
    },


    // O
    {
        { // 0
            { 0, 0, 0, 0 },
            { 0, 4, 4, 0 },
            { 0, 4, 4, 0 },
            { 0, 0, 0, 0 }
        },
        { // 90
            { 0, 0, 0, 0 },
            { 0, 4, 4, 0 },
            { 0, 4, 4, 0 },
            { 0, 0, 0, 0 }
        },
        { // 180
            { 0, 0, 0, 0 },
            { 0, 4, 4, 0 },
            { 0, 4, 4, 0 },
            { 0, 0, 0, 0 }
        },
        { // 270
            { 0, 0, 0, 0 },
            { 0, 4, 4, 0 },
            { 0, 4, 4, 0 },
            { 0, 0, 0, 0 }
        }
    },

    // S
    {
        { // 0
            { 0, 0, 0, 0 },
            { 0, 5, 5, 0 },
            { 5, 5, 0, 0 },
            { 0, 0, 0, 0 }
        },
        { // 90
            { 0, 5, 0, 0 },
            { 0, 5, 5, 0 },
            { 0, 0, 5, 0 },
            { 0, 0, 0, 0 }
        },
        { // 180
            { 0, 0, 0, 0 },
            { 0, 5, 5, 0 },
            { 5, 5, 0, 0 },
            { 0, 0, 0, 0 }
        },
        { // 270
            { 0, 5, 0, 0 },
            { 0, 5, 5, 0 },
            { 0, 0, 5, 0 },
            { 0, 0, 0, 0 }
        }
    },

    // T
    {
        {
            { 0, 0, 0, 0 },
            { 6, 6, 6, 0 },
            { 0, 6, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 6, 0, 0 },
            { 6, 6, 0, 0 },
            { 0, 6, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 6, 0, 0 },
            { 6, 6, 6, 0 },
            { 0, 0, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 6, 0, 0 },
            { 0, 6, 6, 0 },
            { 0, 6, 0, 0 },
            { 0, 0, 0, 0 }
        }
    },

    // Z
    {
        {
            { 0, 0, 0, 0 },
            { 7, 7, 0, 0 },
            { 0, 7, 7, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 0, 7, 0 },
            { 0, 7, 7, 0 },
            { 0, 7, 0, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 0, 0, 0 },
            { 7, 7, 0, 0 },
            { 0, 7, 7, 0 },
            { 0, 0, 0, 0 }
        },
        {
            { 0, 0, 7, 0 },
            { 0, 7, 7, 0 },
            { 0, 7, 0, 0 },
            { 0, 0, 0, 0 }
        }
    }
};

Shape::Shape(ShapeType type)
{
    shapeType   = type;
    rotation    = 0;
    gridPos.x = (PlayField::FIELD_WIDTH / 2) - 2;
    gridPos.y = (type == SHAPE_I) ? 1 : 2;
}

Shape* Shape::createRandom()
{
    return new Shape((ShapeType)(rand() % NUM_OF_SHAPES));
}

void Shape::move(Direction direction)
{
    gridPos = gridPos + Point(direction);
}

void Shape::rotate(Direction direction)
{
    if (direction == Direction::Left)
    {
        rotation = (rotation == 0) ? 3 : (rotation - 1);
    }
    else
    {
        rotation = (rotation + 1) % 4;
    }
}

void Shape::draw(Graphics &graphics, Point origin)
{
    Point screenPos;
    screenPos.x = (gridPos.x * BLOCK_SIZE) + origin.x;
    screenPos.y = ((gridPos.y - PlayField::FIELD_VIS_TOP) * BLOCK_SIZE) + origin.y;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (shapes[shapeType][rotation][y][x] && gridPos.y + y >= PlayField::FIELD_VIS_TOP)
                graphics.draw((ImageId)shapes[shapeType][rotation][y][x], screenPos.x + (x * BLOCK_SIZE), screenPos.y + (y * BLOCK_SIZE));
        }
    }
}

void Shape::draw(Graphics &graphics, int screenX, int screenY)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (shapes[shapeType][rotation][y][x])
                graphics.draw((ImageId)shapes[shapeType][rotation][y][x], screenX + (x * BLOCK_SIZE), screenY + (y * BLOCK_SIZE));
        }
    }
}

Point Shape::getGridPos()
{
    return gridPos;
}

int Shape::getShapeBlock(int x, int y)
{
    if (x < 0 || x > MAX_WIDTH || y < 0 || y > MAX_HEIGHT)
        throw "Out of bounds";

    return shapes[shapeType][rotation][y][x];
}

bool Shape::isEmpty(int x, int y)
{
    return getShapeBlock(x, y) == 0;
}