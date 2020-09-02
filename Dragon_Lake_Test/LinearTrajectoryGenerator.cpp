
#include "LinearTrajectoryGenerator.h"

#include <algorithm>
#include <iostream>

#include "DirectionState.h"

void LinearTrajectoryGenerator::setSegment(Point startp, Point endp) {
	
	startPoint_ = startp;
	endPoint_ = endp;
	currentPoint_ = startPoint_;

	int precision = 8;
	
	int m = 1 << precision;
	long mask = m - 1;

	Point startPointN = startPoint_ * m; 
	Point endPointN = endPoint_ * m;

	signX = endPoint_.x - startPoint_.x;
	signY = endPoint_.y - startPoint_.y;

	
	steps = std::max(labs(endPoint_.x - startPoint_.x), labs(endPoint_.y - startPoint_.y));

	Point maskedStartPoint = { startPointN.x & mask, startPointN.y & mask };

	long u, v;

	if (abs(signX) >= abs(signY)) {
		xPrevails = 1;
		u = endPointN.x - startPointN.x;
		v = endPointN.y - startPointN.y;
		dE = ((maskedStartPoint.y * u) - (maskedStartPoint.x * v)) / m;
	}
	else {
		xPrevails = 0;
		u = endPointN.y - startPointN.y;
		v = endPointN.x - startPointN.x;
		dE = ((maskedStartPoint.x * u) - (maskedStartPoint.y * v)) / m;
	}

	dE = dE << 1;
	d0 = 2 * abs(v) - abs(u);

	if ((u >= 0 && v >= 0) || (u < 0 && v < 0)) {
		d0 += dE;
	}
	else {
		d0 -= dE;
	}

	b = abs(v + v);
	a = abs(u + u) - b;
	signX = sign(signX);
	signY = sign(signY);
}


Point LinearTrajectoryGenerator::advance() {
	if (xPrevails) {
		if (d0 < 0)
			moveX();
		else
			moveXY();
	}
	else {
		if (d0 < 0)
			moveY();
		else
			moveXY();
	}
	return currentPoint_;
}

Point LinearTrajectoryGenerator::next() const {
	if (xPrevails) {
		if (d0 < 0)
			return Point{ currentPoint_.x + signX, currentPoint_.y };
		else
			return Point{ currentPoint_.x + signX, currentPoint_.y + signY };
	}
	else {
		if (d0 < 0)
			return Point{ currentPoint_.x, currentPoint_.y + signY };
		else
			return Point{ currentPoint_.x + signX, currentPoint_.y + signY };
	}
}

void LinearTrajectoryGenerator::moveX() {
	d0 += b;
	currentPoint_.x += signX;
	--steps;
}

void LinearTrajectoryGenerator::moveY() {
	d0 += b;
	currentPoint_.y += signY;
	--steps;
}

void LinearTrajectoryGenerator::moveXY() {
	d0 -= a;
	currentPoint_.y += signY;
	currentPoint_.x += signX;
	--steps;
}

Point LinearTrajectoryGenerator::currentPoint() const {
	return currentPoint_;
}

Point LinearTrajectoryGenerator::startPoint() const {
	return startPoint_;
}

Point LinearTrajectoryGenerator::endPoint() const {
	return endPoint_;
}

