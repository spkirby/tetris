#pragma once
#include "Graphics.h"
#include "Point.h"

enum ShapeType
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

class Shape
{
public:
    static const int MAX_WIDTH = 3;
    static const int MAX_HEIGHT = 3;
    static const int BLOCK_SIZE = 32;
    
    static Shape* Shape::createRandom();

    Shape(ShapeType type);

    void moveLeft();
    void moveRight();
    void moveDown();
    void rotateLeft();
    void rotateRight();
    void draw(Graphics &graphics, Point origin);
    void draw(Graphics &graphics, int screenX, int screenY);
    int getShapeBlock(int x, int y);
    bool isEmpty(int x, int y);
    Point getGridPos();

protected:
    // Array containing all rotations of all shapes.
    // Shapes (7) x rotations (4) x width (4) x height (4)
    static const int shapes[NUM_OF_SHAPES][4][4][4];

    int shapeType;
    int rotation;
    Point gridPos;
};
