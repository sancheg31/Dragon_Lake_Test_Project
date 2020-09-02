#pragma once

#include <vector>

#include "LinearTrajectoryGenerator.h"
#include "Utility.h"




struct Rotation
{
public:
	double x1, y1;
	double x2, y2;
};

class DirectionState
{
public:
	DirectionState(Point p): state(normalize(p)) { }

	DirectionState left() {
		auto p = Point{ (int)(state.x * leftRotation.x1 + state.y * leftRotation.y1),
						(int)(state.x * leftRotation.x2 + state.y * leftRotation.y2) };
		return normalize(p);
	}

	DirectionState right() {
		auto p = Point{ (int)(state.x * rightRotation.x1 + state.y * rightRotation.y1),
						(int)(state.x * rightRotation.x2 + state.y * rightRotation.y2)};
		return normalize(p);
	}

	Point currentDirection() const {
		return state;
	}

private:

	Point normalize(Point p) {
		if (p.x != 0)
			p.x = 1 * sign(p.x);
		if (p.y != 0)
			p.y = 1 * sign(p.y);
	}

	Point state;
	Rotation leftRotation{ sqrt(2) / 2, sqrt(2) / 2, -sqrt(2) / 2, sqrt(2) / 2 };
	Rotation rightRotation{ sqrt(2) / 2, -sqrt(2) / 2, sqrt(2) / 2, sqrt(2) / 2 };
};
