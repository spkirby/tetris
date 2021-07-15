#include <cstring>
#include "Graphics.h"
#include "PlayField.h"
#include "Point.h"
#include "Shape.h"

PlayField::PlayField()
{
    position = Point(550, 50);
    reset();
}

void PlayField::reset()
{
    shape = nullptr;
    animationTime = 0;
    linesToRemove[0] = linesToRemove[1] = linesToRemove[2] = linesToRemove[3] = -1;
    clearField();
}

bool PlayField::hasShape()
{
    return shape != nullptr;
}

void PlayField::setShape(Shape* newShape)
{
    if (shape)
    {
        delete shape;
    }

    if (newShape)
    {
        shapePosition = Point(
            (PlayField::FIELD_WIDTH / 2) - 2,
            (newShape->getType() == ShapeType::SHAPE_I) ? 1 : 2
        );
    }
    else
    {
        shapePosition = Point(0, 0);
    }

    shape = newShape;
}

void PlayField::clearField()
{
    for (int y = 0; y < FIELD_HEIGHT; y++)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            if (x == 0 || x == FIELD_WIDTH - 1 || y == FIELD_HEIGHT - 1)
            {
                setBlock(x, y, ImageId::Boundary);
            }
            else
            {
                setBlock(x, y, ImageId::BlockEmpty);
            }
        }
    }
}

void PlayField::render(Graphics& graphics)
{
    bool flashLine;
    int ltrIndex = 0;

    for (int y = FIELD_VIS_TOP; y < FIELD_HEIGHT; y++)
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
                imgIndex = getBlock(x, y);
            }

            Point offset(x * Shape::BLOCK_SIZE, (y - FIELD_VIS_TOP) * Shape::BLOCK_SIZE);
            graphics.renderImage(imgIndex, position + offset);
        }
    }

    if (shape)
    {
        SDL_Rect rect =
        {
            position.x,
            position.y,
            FIELD_WIDTH * Shape::BLOCK_SIZE,
            (FIELD_HEIGHT - FIELD_VIS_TOP) * Shape::BLOCK_SIZE,
        };

        graphics.setClippingRect(&rect);

        Point offset = Point(shapePosition.x * Shape::BLOCK_SIZE, (shapePosition.y - FIELD_VIS_TOP) * Shape::BLOCK_SIZE);
        shape->position = position + offset;
        shape->render(graphics);

        graphics.setClippingRect(nullptr);
    }
}

void PlayField::drawOutline(Graphics& graphics)
{
    for (int y = FIELD_HEIGHT - 1; y >= FIELD_VIS_TOP; y--)
    {
        for (int x = 0; x < FIELD_WIDTH; x++)
        {
            if (getBlock(x, y) == ImageId::Boundary)
            {
                Point offset(x * Shape::BLOCK_SIZE, (y - FIELD_VIS_TOP) * Shape::BLOCK_SIZE);
                graphics.renderImage(ImageId::Boundary, position + offset);
            }
        }
    }
}

ImageId PlayField::getBlock(int x, int y)
{
    return field[y][x];
}

ImageId PlayField::setBlock(int x, int y, ImageId value)
{
    return field[y][x] = value;
}

bool PlayField::isValidMove(Point& newPosition, Shape& shape)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (!shape.isEmpty(x, y) && getBlock(newPosition.x + x, newPosition.y + y) != ImageId::BlockEmpty)
            {
                return false;
            }
        }
    }

    return true;
}

int PlayField::checkForCompletedLines()
{
    if (!shape) return 0;

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
        animationTime = INITIAL_ANIMATION_TIME;
    }

    return linesComplete;
}

bool PlayField::isLineComplete(int line)
{
    bool complete = true;

    for (int x = 1; complete && x < FIELD_WIDTH - 1; x++)
    {
        if (getBlock(x, line) == ImageId::BlockEmpty)
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

bool PlayField::tryMoveShape(Direction direction)
{
    if (shape)
    {
        Point newPosition = shapePosition + Point(direction);

        if (isValidMove(newPosition, *shape))
        {
            shapePosition = newPosition;
            return true;
        }
    }

    return false;
}

bool PlayField::tryRotateShape(Direction direction)
{
    if (shape && (direction == Direction::Left || direction == Direction::Right))
    {
        Shape shapeCopy(*shape);
        shapeCopy.rotate(direction);
        
        if (isValidMove(shapePosition, shapeCopy))
        {
            shape->rotate(direction);
            return true;
        }
    }

    return false;
}

bool PlayField::tryAbsorbShape(int& completedLines)
{
    if (!shape || !isShapeInsideField())
    {
        return false;
    }

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (!shape->isEmpty(x, y))
            {
                setBlock(shapePosition.x + x, shapePosition.y + y, shape->getShapeBlock(x, y));
            }
        }
    }

    setShape(nullptr);
    completedLines = checkForCompletedLines();

    return true;
}


bool PlayField::isShapeInsideField()
{
    if (!shape) return false;

    for (int y = shapePosition.y; y < FIELD_VIS_TOP; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (!shape->isEmpty(x, y))
            {
                return false;
            }
        }
    }

    return true;
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
