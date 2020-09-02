#pragma once

#include <utility>

#include "Utility.h"

class DirectionState;

/*
Represents point movement along the line on pixel field
Used by BulletObject and EnemyObject
*/
class LinearTrajectoryGenerator 
{
public:

	void setSegment(Point start, Point end);
	Point advance();

	Point startPoint() const;
	Point endPoint() const;
	Point currentPoint() const;
	Point next() const;

private:

	void moveX();
	void moveY();
	void moveXY();

	long d0, dE, a, b;
	Point startPoint_;
	Point endPoint_;
	Point currentPoint_;
	int signX, signY;
	int xPrevails;
	int steps;
};
