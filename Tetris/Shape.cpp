#include "Enums.h"
#include "Graphics.h"
#include "PlayField.h"
#include "Point.h"
#include "Shape.h"
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

const int Shape::shapes[(int)ShapeType::NUM_OF_SHAPES][4][4][4] =
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
    shapeType = type;
    rotation = 0;
}

Shape* Shape::createRandom()
{
    return new Shape((ShapeType)(rand() % (int)ShapeType::NUM_OF_SHAPES));
}

ImageId Shape::getShapeBlock(int x, int y)
{
    if (x < 0 || x > MAX_WIDTH || y < 0 || y > MAX_HEIGHT)
    {
        throw std::out_of_range("Position is out of bounds");
    }

    return (ImageId)shapes[(int)shapeType][rotation][y][x];
}

ShapeType Shape::getType()
{
    return shapeType;
}

bool Shape::isEmpty(int x, int y)
{
    return getShapeBlock(x, y) == ImageId::BlockEmpty;
}

void Shape::render(Graphics& graphics)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            ImageId block = getShapeBlock(x, y);

            if (block != ImageId::BlockEmpty /*&& gridPos.y + y >= PlayField::FIELD_VIS_TOP*/)
            {
                Point offset(x * BLOCK_SIZE, y * BLOCK_SIZE);
                graphics.renderImage(block, position + offset);
            }
        }
    }
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
