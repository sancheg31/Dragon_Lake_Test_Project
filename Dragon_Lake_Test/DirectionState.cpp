#include "DirectionState.h"

#include <cmath>

DirectionState::DirectionState(Point p) :	state(p), 
											leftRotation{ sqrt(2) / 2, sqrt(2) / 2, -sqrt(2) / 2, sqrt(2) / 2 }, 
											rightRotation{ sqrt(2) / 2, -sqrt(2) / 2, sqrt(2) / 2, sqrt(2) / 2 } { }

DirectionState DirectionState::left() const {
	double x = state.x * leftRotation.x1 + state.y * leftRotation.y1;
	double y = state.x * leftRotation.x2 + state.y * leftRotation.y2;
	Point p = normalize(x, y);
	return  DirectionState{ p };
}

DirectionState DirectionState::right() const {
	double x = state.x * rightRotation.x1 + state.y * rightRotation.y1;
	double y = state.x * rightRotation.x2 + state.y * rightRotation.y2;
	Point p = normalize(x, y);
	return  DirectionState{ p };
}

Point DirectionState::currentDirection() const {
	return state;
}

Point DirectionState::normalize(double x, double y) const {
	Point p{ 0, 0 };
	if (x != 0) {
		p.x = 1 * sign(x);
	}
	if (y != 0) {
		p.y = 1 * sign(y);
	}
	return p;
}
