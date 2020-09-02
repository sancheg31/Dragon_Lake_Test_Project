#pragma once

struct Point;
struct Size;

struct Point
{
	int x;
	int y;

};

struct Size
{
	int width;
	int height;

	explicit operator Point() const {
		return Point{ width, height };
	}
};

template <typename T>
int sign(T val) {
	return (T(0) < val) - (T(0) > val);
}

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

inline Size operator+(const Size& p1, const Size& p2) {
	return Size{ p1.width + p2.width, p1.height + p2.height };
}

inline Size operator-(const Size& p1, const Size& p2) {
	return Size{ p1.width - p2.width, p1.height - p2.height };
}
 
inline Size operator*(const Size& p, int val) {
	return Size{ p.width * val, p.height * val };
}

inline Size operator*(int val, const Size& p) {
	return Size{ p.width * val, p.height * val };
}

inline Size operator/(const Size& p, int val) {
	return Size{ p.width / val, p.height / val };
}

inline bool operator==(const Size& p1, const Size& p2) {
	return (p1.width == p2.width) && (p1.height == p2.height);
}

inline bool operator!=(const Size& p1, const Size& p2) {
	return (p1.width != p2.width) || (p1.height != p2.height);
}



