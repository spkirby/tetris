#pragma once
#include <array>
#include <optional>
#include "Enums.h"
#include "Graphics.h"
#include "Point.h"
#include "Shape.h"

class PlayField
{
public:
    Point position;

    PlayField();
    void drawOutline(Graphics& graphics);
    int getCompletedLineCount();
    bool hasShape();
    bool isAnimating();
    void render(Graphics& graphics);
    void reset();
    void setShapeType(ShapeType newShape);
    bool tryAbsorbShape();
    bool tryMoveShape(Direction direction);
    bool tryRotateShape(Direction direction);
    bool update();

protected:
    static const int FIELD_WIDTH = 12;
    static const int FIELD_HEIGHT = 25;
    static const int FIELD_VIS_TOP = 4;  // First visible line of the PlayField
    static const int INITIAL_ANIMATION_TIME = 30;

    ImageId field[FIELD_HEIGHT][FIELD_WIDTH];
    int animationTime;  // Amount of time for which the field will animate
    std::array<bool, FIELD_HEIGHT> completedLines;
    std::optional<Shape> shape;
    Point shapePosition;

    void clearField();
    void clearLine(int line);
    ImageId getBlock(int x, int y);
    bool isShapeInsideField();
    bool isValidMove(Point& newPosition, Shape& shape);
    void removeLine(int line);
    ImageId setBlock(int x, int y, ImageId value);
    void updateCompletedLines();
};
