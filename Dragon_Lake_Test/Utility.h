#pragma once

struct Point
{
	int x;
	int y;

	friend Point operator+(const Point& p1, const Point& p2) {
		return Point{ p1.x + p2.x, p1.y + p2.y };
	}

	friend Point operator-(const Point& p1, const Point& p2) {
		return Point{ p1.x - p2.x, p1.y - p2.y };
	}

	friend Point operator*(const Point& p, int val) {
		return Point{ p.x * val, p.y * val };
	}

	friend Point operator*(int val, const Point& p) {
		return Point{ p.x * val, p.y * val };
	}

	friend Point operator/(const Point& p, int val) {
		return Point{ p.x * val, p.y * val };
	}
};

struct Size
{
	int width;
	int height;
};