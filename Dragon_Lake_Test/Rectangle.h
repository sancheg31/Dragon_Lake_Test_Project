#pragma once


#include "Utility.h"

class GameObject;

enum class VertexPosition {
	UP_RIGHT,
	UP_LEFT,
	DOWN_LEFT,
	DOWN_RIGHT
};

class Rectangle
{
public:

	Rectangle(Point p, Size dim, VertexPosition position);
	Rectangle(const GameObject& object);

	Rectangle(const Rectangle&) = default;
	Rectangle(Rectangle&&) = default;
	Rectangle& operator=(const Rectangle&) = default;
	Rectangle& operator=(Rectangle&&) = default;
	~Rectangle() = default;

	bool isContained(Point p) const;

	bool isCollide(Rectangle rect) const;

	Point center() const;

	Point upLeft() const;
	Point upRight() const;
	Point downRight() const;
	Point downLeft() const;

private:

	void constructFromUpperLeft(Point p, Size dimensions);

	struct Projection;

	Point upLeft_;
	Point downRight_;
	
};

