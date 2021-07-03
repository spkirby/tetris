#pragma once
#include "Graphics.h"
#include "Shape.h"
#include "structs.h"

class PlayField
{
public:
    PlayField();
    void draw(Graphics& graphics);
    void drawOutline(Graphics& graphics);
    bool update();
    void reset();
    Point getScreenPos();
    bool checkValidMove(int newX, int newY, Shape& shape);
    int checkForLines(Shape *shape);
    bool isShapeInsideField(Shape &shape);
    bool isAnimating();
    void absorbShape(Shape& shape);

    static const int FIELD_WIDTH   = 12;
    static const int FIELD_HEIGHT  = 25;
    static const int FIELD_VIS_TOP = 4;  // First visible line of the PlayField

protected:
    bool isLineComplete(int line);
    void removeLine(int line);

    static const int DEFAULT_ANIM_TIME = 24;

    Point screenPos;
    int field[FIELD_HEIGHT][FIELD_WIDTH];
    int animationTime;  // Amount of time for which the field will animate
    int linesToRemove[4];
};
