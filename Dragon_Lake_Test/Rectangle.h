#pragma once


#include "Utility.h"

class GameObject;

enum class VertexPosition {
	UP_RIGHT,
	UP_LEFT,
	DOWN_LEFT,
	DOWN_RIGHT
};


/*
Helper class Rectangle for misc point calculations
*/
class Rectangle
{
public:

	Rectangle(Point p, Size dim, VertexPosition position);
	Rectangle(GameObject* object);

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

	int width() const;
	int height() const;

	Size size() const;

private:

	void constructFromUpperLeft(Point p, Size dimensions);

	struct Projection;

	Point upLeft_;
	Point downRight_;
	
};

Point centerPoint(GameObject* object);

Rectangle scale(Rectangle rect, double multiplier);