#ifndef SHAPE_H
#define SHAPE_H

class Shape;

#include "PlayField.h"
#include "structs.h"

class Shape
{
public:
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

	Shape(ShapeType type, PlayField &field, Graphics &graphics);
	bool moveLeft();
	bool moveRight();
	bool moveDown();
	bool rotateLeft();
	bool rotateRight();
	bool stop();
	void draw();
	void draw(int screenX, int screenY);
	Point getGridPos();

	static const int BLOCK_SIZE = 32;

protected:
	// Array containing all rotations of all shapes.
	// Shapes (7) x rotations (4) x width (4) x height (4)
	static const int shapes[NUM_OF_SHAPES][4][4][4];

    Graphics &graphics;
	int shapeType;
	int rotation;
	PlayField &parentField;
	Point fieldPos;
	Point gridPos;

private:
};

#endif // SHAPE_H
