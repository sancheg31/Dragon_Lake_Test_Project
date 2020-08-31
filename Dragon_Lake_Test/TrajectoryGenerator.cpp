
#include "TrajectoryGenerator.h"

#include <algorithm>
#include <iostream>

void TrajectoryGenerator::setSegment(Line line, int precision) {
	Point startPoint = line.start;
	Point endPoint = line.end;
	int m = 1 << precision;
	long mask = m - 1;

	Point startPointN = Point{ startPoint.x * m, startPoint.y * m };
	Point endPointN = Point{ endPoint.x * m, endPoint.y * m };

	signX = endPoint.x - startPoint.x;
	signY = endPoint.y - startPoint.y;

	start = startPoint;
	steps = std::max(labs(endPoint.x - startPoint.x), labs(endPoint.y - startPoint.y));

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

/*virtual*/ Point TrajectoryGenerator::next() {
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
	return start;
}

void TrajectoryGenerator::moveX() {
	d0 += b;
	start.x += signX;
	--steps;
}

void TrajectoryGenerator::moveY() {
	d0 += b;
	start.y += signY;
	--steps;
}

void TrajectoryGenerator::moveXY() {
	d0 -= a;
	start.y += signY;
	start.x += signX;
	--steps;
}
