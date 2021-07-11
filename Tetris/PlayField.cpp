#include <cstring>
#include "PlayField.h"
#include "Graphics.h"
#include "Shape.h"

PlayField::PlayField()
{
    screenPos.x = 550;
    screenPos.y = 50;

    reset();
}

void PlayField::reset()
{
    animationTime = 0;

    linesToRemove[0] = linesToRemove[1] = linesToRemove[2] = linesToRemove[3] = -1;

    for (int y = 0; y < FIELD_HEIGHT - 1; y++)
    {
        for (int x = 1; x < FIELD_WIDTH - 1; x++)
        {
            field[y][x] = ImageId::BlockEmpty;
        }
    }

    for(int y=0; y < FIELD_HEIGHT; y++)
    {
        field[y][0] = ImageId::Boundary;
        field[y][FIELD_WIDTH-1] = ImageId::Boundary;
    }

    for (int x = 1; x < FIELD_WIDTH - 1; x++)
    {
        field[FIELD_HEIGHT - 1][x] = ImageId::Boundary;
    }
}

void PlayField::draw(Graphics& graphics)
{
    bool flashLine;
    int ltrIndex = 0;

    for (int y = FIELD_HEIGHT - 1; y >= FIELD_VIS_TOP; y--)
    {
        flashLine = false;

        if (ltrIndex < 4 && y == linesToRemove[ltrIndex])
        {
            flashLine = (animationTime > 0 && (animationTime / 3) % 2 == 0);
            ltrIndex++;
        }

        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            ImageId imgIndex;

            if (flashLine && x > 0 && x < FIELD_WIDTH - 1)
            {
                imgIndex = ImageId::BlockEmpty;
            }
            else
            {
                imgIndex = field[y][x];
            }

            Point offset(x * Shape::BLOCK_SIZE, (y - FIELD_VIS_TOP) * Shape::BLOCK_SIZE);

            graphics.renderImage(imgIndex, screenPos + offset);
        }
    }
}

void PlayField::drawOutline(Graphics& graphics)
{
    for (int y = FIELD_HEIGHT - 1; y >= FIELD_VIS_TOP; y--)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            if (field[y][x] == ImageId::Boundary)
            {
                Point offset(x * Shape::BLOCK_SIZE, (y - FIELD_VIS_TOP) * Shape::BLOCK_SIZE);
                graphics.renderImage(ImageId::Boundary, screenPos + offset);
            }
        }
    }
}

Point PlayField::getScreenPos()
{
    return screenPos;
}

bool PlayField::isValidMove(Point& newPosition, Shape& shape)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (!shape.isEmpty(x, y) && field[newPosition.y + y][newPosition.x + x] != ImageId::BlockEmpty)
            {
                return false;
            }
        }
    }

    return true;
}

int PlayField::checkForLines(Shape* shape)
{
    int line = FIELD_HEIGHT - 2;
    int linesComplete = 0;

    linesToRemove[0] = -1;
    linesToRemove[1] = -1;
    linesToRemove[2] = -1;
    linesToRemove[3] = -1;

    while (line > 0)
    {
        if (isLineComplete(line))
        {
            linesToRemove[linesComplete] = line;
            linesComplete++;
        }

        line--;
    }

    if (linesComplete)
    {
        animationTime = DEFAULT_ANIM_TIME;
    }

    return linesComplete;
}

bool PlayField::isLineComplete(int line)
{
    bool complete = true;

    for (int x = 1; complete && x < FIELD_WIDTH - 1; x++)
    {
        if (field[line][x] == ImageId::BlockEmpty)
        {
            complete = false;
        }
    }

    return complete;
}

void PlayField::removeLine(int line)
{
    memmove(field[1], field[0], sizeof(int) * FIELD_WIDTH * line);
    memset(field[0] + 1, 0, FIELD_WIDTH - 2);
}

bool PlayField::isShapeInsideField(Shape &shape)
{
    Point shapePos = shape.getGridPos();

    for (int y = 0; y < 4 && (shapePos.y + y < FIELD_VIS_TOP); y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (!shape.isEmpty(x, y))
            {
                return false;
            }
        }
    }

    return true;
}

void PlayField::absorbShape(Shape& shape)
{
    Point shapePos = shape.getGridPos();

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (!shape.isEmpty(x, y))
            {
                field[shapePos.y + y][shapePos.x + x] = shape.getShapeBlock(x, y);
            }
        }
    }
}

bool PlayField::isAnimating()
{
    return animationTime > 0;
}

bool PlayField::update()
{
    bool linesRemoved = false;

    if (isAnimating() && --animationTime == 0)
    {
        for (int i = 3; i >= 0; i--)
        {
            if (linesToRemove[i] != -1)
            {
                removeLine(linesToRemove[i]);
                linesRemoved = true;
            }

            linesToRemove[i] = -1;
        }
    }

    return linesRemoved;
}
