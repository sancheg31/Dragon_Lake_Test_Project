#pragma once

#include "Utility.h"

template <typename T>
T sign(T val) {
	return (T(0) < val) - (T(0) > val);
}

class LinearTrajectoryGenerator 
{
public:

	void setSegment(Point start, Point end, int precision);
	Point advance();
	Point next() const;;

private:

	void moveX();
	void moveY();
	void moveXY();

	long d0, dE, a, b;
	Point startPoint;
	Point endPoint;
	Point currentPoint;
	int signX, signY;
	int xPrevails;
	int steps;
};
