#pragma once


#include <vector>
#include <cmath>

#include "LinearTrajectoryGenerator.h"
#include "Utility.h"

#include <iostream>
#include <numeric>


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
	DirectionState(Point p): state(p) { }

	DirectionState left() {
		double x = state.x * leftRotation.x1 + state.y * leftRotation.y1;
		double y = state.x * leftRotation.x2 + state.y * leftRotation.y2;
		Point p = normalize(x, y);
		return  DirectionState{ p };
	}

	DirectionState right() {
		double x = state.x * rightRotation.x1 + state.y * rightRotation.y1;
		double y = state.x * rightRotation.x2 + state.y * rightRotation.y2;
		Point p = normalize(x, y);
		return  DirectionState{ p };
	}

	Point currentDirection() const {
		return state;
	}

private:

	Point normalize(double x, double y) {
		Point p{ 0, 0 };
		if (x != 0) {
			p.x = 1 * sign(x);
		}
		if (y != 0) {
			p.y = 1 * sign(y);
		}
		return p;
	}

	Point state;
	Rotation leftRotation{ sqrt(2) / 2, sqrt(2) / 2, -sqrt(2) / 2, sqrt(2) / 2 };
	Rotation rightRotation{ sqrt(2) / 2, -sqrt(2) / 2, sqrt(2) / 2, sqrt(2) / 2 };
};
