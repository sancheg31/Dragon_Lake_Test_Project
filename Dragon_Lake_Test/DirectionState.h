#pragma once

#include "Utility.h"


struct Rotation
{
public:
	double x1;
	double y1;
	double x2;
	double y2;
};

class DirectionState
{
public:
	DirectionState(Point p);

	DirectionState left() const;
	DirectionState right() const;
	Point currentDirection() const;

private:

	Point normalize(double x, double y) const;

	Point state;
	Rotation leftRotation;
	Rotation rightRotation;
};
