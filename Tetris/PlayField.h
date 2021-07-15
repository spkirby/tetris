#pragma once
#include "Entity.h"
#include "Enums.h"
#include "Graphics.h"
#include "Point.h"
#include "Shape.h"

class PlayField : public Entity
{
public:
    PlayField();
    void drawOutline(Graphics& graphics);
    bool hasShape();
    bool isAnimating();
    void render(Graphics& graphics);
    void reset();
    void setShape(Shape* newShape);
    bool tryAbsorbShape(int& completedLines);
    bool tryMoveShape(Direction direction);
    bool tryRotateShape(Direction direction);
    bool update();

protected:
    static const int FIELD_WIDTH = 12;
    static const int FIELD_HEIGHT = 25;
    static const int FIELD_VIS_TOP = 4;  // First visible line of the PlayField
    static const int INITIAL_ANIMATION_TIME = 24;

    ImageId field[FIELD_HEIGHT][FIELD_WIDTH];
    int animationTime;  // Amount of time for which the field will animate
    int linesToRemove[4];
    Shape* shape;
    Point shapePosition;

    int checkForCompletedLines();
    void clearField();
    ImageId getBlock(int x, int y);
    bool isLineComplete(int line);
    bool isShapeInsideField();
    bool isValidMove(Point& newPosition, Shape& shape);
    void removeLine(int line);
    ImageId setBlock(int x, int y, ImageId value);
};
