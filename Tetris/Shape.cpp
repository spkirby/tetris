#include "Shape.h"
#include "PlayField.h"
#include "Graphics.h"
#include <stdio.h>

const int Shape::shapes[NUM_OF_SHAPES][4][4][4] =
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


Shape::Shape(ShapeType type, PlayField *field)
{
	shapeType   = type;
	parentField = field;
	rotation    = 0;

	fieldPos = parentField->getScreenPos();

	gridPos.x = (PlayField::FIELD_WIDTH / 2) - 2;
	gridPos.y = (type == SHAPE_I) ? 1 : 2;
}


bool Shape::moveLeft()
{
	if( parentField->checkValidMove(gridPos.x-1, gridPos.y, shapes[shapeType][rotation]) )
	{
		gridPos.x--;
		return true;
	}

	return false;
}


bool Shape::moveRight()
{
	if( parentField->checkValidMove(gridPos.x+1, gridPos.y, shapes[shapeType][rotation]) )
	{
		gridPos.x++;
		return true;
	}

	return false;
}


bool Shape::moveDown()
{
	if( parentField->checkValidMove(gridPos.x, gridPos.y+1, shapes[shapeType][rotation]) )
	{
		gridPos.y++;
		return true;
	}

	return false;
}


bool Shape::rotateLeft()
{
	int newRot = (rotation == 0) ? 3 : (rotation-1);

	if( parentField->checkValidMove(gridPos.x, gridPos.y, shapes[shapeType][newRot]) )
	{
		rotation = newRot;
		return true;
	}

	return false;
}


bool Shape::rotateRight()
{
	int newRot = (rotation+1) % 4;

	if( parentField->checkValidMove(gridPos.x, gridPos.y, shapes[shapeType][newRot]) )
	{
		rotation = newRot;
		return true;
	}

	return false;
}


bool Shape::stop()
{
	return parentField->absorbShape(gridPos, shapes[shapeType][rotation]);
}


void Shape::draw()
{
	Point screenPos;
	screenPos.x = (gridPos.x * BLOCK_SIZE) + fieldPos.x;
	screenPos.y = ((gridPos.y - PlayField::FIELD_VIS_TOP) * BLOCK_SIZE) + fieldPos.y;

	for(int y=0; y<4; y++)
		for(int x=0; x<4; x++)
		{
			if(shapes[shapeType][rotation][y][x] && gridPos.y + y >= PlayField::FIELD_VIS_TOP)
				Graphics::draw((Graphics::ImageID)shapes[shapeType][rotation][y][x], screenPos.x + (x * BLOCK_SIZE), screenPos.y + (y * BLOCK_SIZE));
		}
}


void Shape::draw(int screenX, int screenY)
{
	for(int y=0; y<4; y++)
		for(int x=0; x<4; x++)
		{
			if(shapes[shapeType][rotation][y][x])
				Graphics::draw((Graphics::ImageID)shapes[shapeType][rotation][y][x], screenX + (x * BLOCK_SIZE), screenY + (y * BLOCK_SIZE));
		}
}


Point Shape::getGridPos()
{
	return gridPos;
}
