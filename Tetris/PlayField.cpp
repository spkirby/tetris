#include <cstring>
#include "PlayField.h"
#include "Graphics.h"
#include "Shape.h"

PlayField::PlayField(Graphics& graphics) :
    graphics(graphics)
{
	screenPos.x = 550;
	screenPos.y = 50;

	reset();
}


void PlayField::reset()
{
	animationTime = 0;

	linesToRemove[0] = linesToRemove[1] = linesToRemove[2] = linesToRemove[3] = -1;

	for(int y=0; y < FIELD_HEIGHT-1; y++)
		for(int x=1; x < FIELD_WIDTH-1; x++)
			field[y][x] = IMAGE_BLOCK_EMPTY;

	for(int y=0; y < FIELD_HEIGHT; y++)
	{
		field[y][0] = IMAGE_BOUNDARY;
		field[y][FIELD_WIDTH-1] = IMAGE_BOUNDARY;
	}

	for(int x=1; x < FIELD_WIDTH-1; x++)
		field[FIELD_HEIGHT-1][x] = IMAGE_BOUNDARY;
}


void PlayField::draw()
{
	bool flashLine;
	int ltrIndex = 0;

	for(int y=FIELD_HEIGHT-1; y >= FIELD_VIS_TOP; y--)
	{
		flashLine = false;

		if(ltrIndex < 4 && y == linesToRemove[ltrIndex])
		{
			flashLine = (animationTime > 0 && (animationTime / 3) % 2 == 0);
			ltrIndex++;
		}

		for(int x=0; x < FIELD_WIDTH; x++)
		{
			int imgIndex;

			if(flashLine && x > 0 && x < FIELD_WIDTH - 1)
				imgIndex = IMAGE_BLOCK_EMPTY;
			else
				imgIndex = IMAGE_BLOCK_EMPTY + field[y][x];

			graphics.draw((ImageId)imgIndex,
				screenPos.x + (x * Shape::BLOCK_SIZE),
				screenPos.y + ((y - FIELD_VIS_TOP) * Shape::BLOCK_SIZE));
		}
	}
}

void PlayField::drawOutline()
{
	for(int y=FIELD_HEIGHT-1; y >= FIELD_VIS_TOP; y--)
	{
		for(int x=0; x < FIELD_WIDTH; x++)
		{
			if(field[y][x] == IMAGE_BOUNDARY)
			{
				graphics.draw(IMAGE_BOUNDARY,
					screenPos.x + (x * Shape::BLOCK_SIZE),
					screenPos.y + ((y - FIELD_VIS_TOP) * Shape::BLOCK_SIZE));
			}
		}
	}
}

Point PlayField::getScreenPos()
{
	return screenPos;
}


bool PlayField::checkValidMove(int newX, int newY, const int shape[4][4])
{
	bool valid = true;

	for(int y=0; y<4 && valid; y++)
		for(int x=0; x<4 && valid; x++)
			if(shape[y][x] && field[newY + y][newX + x])
				valid = false;

	return valid;
}


int PlayField::checkForLines(Shape* shape)
{
	int line = FIELD_HEIGHT - 2;
	int linesComplete = 0;

	linesToRemove[0] = -1;
	linesToRemove[1] = -1;
	linesToRemove[2] = -1;
	linesToRemove[3] = -1;

	while(line > 0)
	{
		if(isLineComplete(line))
		{
			linesToRemove[linesComplete] = line;
			linesComplete++;
		}

		line--;
	}

	if(linesComplete)
		animationTime = DEFAULT_ANIM_TIME;

	return linesComplete;
}


bool PlayField::isLineComplete(int line)
{
	bool complete = true;

	for(int x=1; complete && x < FIELD_WIDTH-1; x++)
		if(field[line][x] == 0)
			complete = false;

	return complete;
}


void PlayField::removeLine(int line)
{
	memmove(field[1], field[0], sizeof(int) * FIELD_WIDTH * line);
	memset(field[0]+1, 0, FIELD_WIDTH-2);
}


bool PlayField::absorbShape(Point shapePos, const int shape[4][4])
{
	bool insideField = true;

	for(int y=0; y<4; y++)
		for(int x=0; x<4; x++)
			if(shape[y][x])
			{
				field[shapePos.y + y][shapePos.x + x] = shape[y][x];

				if(shapePos.y + y < FIELD_VIS_TOP)
					insideField = false;
			}

			return insideField;
}


bool PlayField::isAnimating()
{
	return (animationTime > 0);
}


bool PlayField::update()
{
	bool linesRemoved = false;

	if(isAnimating() && --animationTime == 0)
	{
		for(int i=3; i >= 0; i--)
		{
			if(linesToRemove[i] != -1)
			{
				removeLine(linesToRemove[i]);
				linesRemoved = true;
			}

			linesToRemove[i] = -1;
		}
	}

	return linesRemoved;
}
