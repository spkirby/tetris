#pragma once
#include "Entity.h"
#include "Enums.h"
#include "Graphics.h"
#include "Point.h"

enum class ShapeType
{
    SHAPE_I,
    SHAPE_J,
    SHAPE_L,
    SHAPE_O,
    SHAPE_S,
    SHAPE_T,
    SHAPE_Z,
    NUM_OF_SHAPES
};

class Shape : public Entity
{
public:
    static const int MAX_WIDTH = 3;
    static const int MAX_HEIGHT = 3;
    static const int BLOCK_SIZE = 32;
    static Shape* Shape::createRandom();

    Point position;

    Shape(ShapeType type);
    ImageId getShapeBlock(int x, int y);
    ShapeType getType();
    bool isEmpty(int x, int y);
    void render(Graphics& graphics);
    void rotate(Direction direction);

protected:
    // Array containing all rotations of all shapes.
    // Shapes (7) x rotations (4) x width (4) x height (4)
    static const int shapes[(int)ShapeType::NUM_OF_SHAPES][4][4][4];

    ShapeType shapeType;
    int rotation;
};
