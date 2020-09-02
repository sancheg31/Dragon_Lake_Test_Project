#pragma once

#include "Utility.h"

#include <utility>


class DirectionState;

template <typename T>
int sign(T val) {
	return (T(0) < val) - (T(0) > val);
}

class LinearTrajectoryGenerator 
{
public:

	void setSegment(Point start, Point end);
	Point advance();
	Point next() const;

	std::pair<DirectionState, DirectionState> possibleStates() const;

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
