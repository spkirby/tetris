#pragma once
#include "Enums.h"
#include "Graphics.h"
#include "Point.h"

enum class ShapeType
{
    ShapeI,
    ShapeJ,
    ShapeL,
    ShapeO,
    ShapeS,
    ShapeT,
    ShapeZ,
    Count
};

class Shape
{
public:
    static const int MAX_WIDTH = 3;
    static const int MAX_HEIGHT = 3;
    static const int BLOCK_SIZE = 32;

    Point position;

    Shape(ShapeType type);
    Shape(ShapeType type, Point position);
    ImageId getShapeBlock(int x, int y);
    ShapeType getType();
    bool isEmpty(int x, int y);
    void render(Graphics& graphics);
    void rotate(Direction direction);

protected:
    // Array containing all rotations of all shapes.
    // Shapes (7) x rotations (4) x width (4) x height (4)
    static const unsigned char shapes[(int)ShapeType::Count][4][4][4];

    ShapeType shapeType;
    int rotation;
};
