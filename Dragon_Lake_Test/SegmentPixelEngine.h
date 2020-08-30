#pragma once

#include "Utility.h"

template <typename T>
T sign(T val) {
	return (T(0) > val) - (T(0) < val);
}

class SegmentPixelEngine {
public:

	void setSegment(Line line, int precision);
	Point next();

private:

	void moveX();
	void moveY();
	void moveXY();

	long d0, dE, a, b;
	Point start;
	int signX, signY;
	int xPrevails;
	int steps;
};
