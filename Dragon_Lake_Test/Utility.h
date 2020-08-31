#pragma once

struct Point
{
	int x;
	int y;
};

struct Trajectory
{
	Point start;
	Point end;
};

struct Size
{
	int width;
	int height;
};

inline Point operator+(const Point& p1, const Point& p2) {
	return Point{ p1.x + p2.x, p1.y + p2.y };
}

inline Point operator-(const Point& p1, const Point& p2) {
	return Point{ p1.x - p2.x, p1.y - p2.y };
}

inline Point operator*(const Point& p, int val) {
	return Point{ p.x * val, p.y * val };
}

inline Point operator*(int val, const Point& p) {
	return Point{ p.x * val, p.y * val };
}

inline Point operator/(const Point& p, int val) {
	return Point{ p.x / val, p.y / val };
}

inline bool operator==(const Point& p1, const Point& p2) {
	return (p1.x == p2.x) && (p1.y == p2.y);
}

inline bool operator!=(const Point & p1, const Point & p2) {
	return (p1.x != p2.x) || (p1.y != p2.y);
}




