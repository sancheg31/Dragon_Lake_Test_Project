#pragma once

#include <utility>

#include "Utility.h"

enum class VertexPosition {
	UP_RIGHT,
	UP_LEFT,
	DOWN_LEFT,
	DOWN_RIGHT
};

class Rectangle
{
public:

	Rectangle(Point p, Size dim, VertexPosition position): dimensions(dim)  {
		switch (position) {
		case VertexPosition::UP_RIGHT:
			constructFromUpperLeft(Point{ p.x - dimensions.width, p.y }, dimensions);
			break;
		case VertexPosition::UP_LEFT:
			constructFromUpperLeft(p, dimensions);
			break;
		case VertexPosition::DOWN_LEFT:
			constructFromUpperLeft(Point{ p.x, p.y - dimensions.height }, dimensions);
			break;
		case VertexPosition::DOWN_RIGHT:
			constructFromUpperLeft(Point{ p.x - dimensions.width, p.y - dimensions.height }, dimensions);
			break;
		}
	}

	bool isContained(Point p) const {
		return (p.x >= upLeft.x && p.x <= downRight.x && p.y >= upLeft.y && p.y <= downRight.y);
	}

	bool isCollide(Rectangle rect) const {

		Projection x{ upLeft.x, downRight.x };
		Projection y{ upLeft.y, downRight.y };
		Projection xrect{ rect.upLeft.x, rect.downRight.x };
		Projection yrect{ rect.upLeft.y, rect.downRight.y };

		bool interceptsX = xfirst.isBetween(xsecond.first) || xfirst.isBetween(xsecond.second);
		bool interceptsY = yfirst.isBetween(ysecond.first) || yfirst.isBetween(ysecond.second);
		return interceptsX && interceptsY;
	}

	Rectangle(const Rectangle&) = default;
	Rectangle(Rectangle&&) = default;
	~Rectangle() = default;

private:

	struct Projection
	{
		int first;
		int second;
		
		bool isValueBetween(int val)	{
			auto [less, bigger] = (first < second) ? std::pair{first, second} : std::pair{second, first};
			return val >= less && val <= bigger;
		}
	};



	void constructFromUpperLeft(Point p, Size dimensions) {
		upLeft = p;
		upRight = Point{ p.x + dimensions.width, p.y };
		downLeft = Point{ p.x, p.y + dimensions.height };
		downRight = Point{ p.x + dimensions.width, p.y + dimensions.height };
	}

	Size dimensions;
	Point upLeft;
	Point upRight;
	Point downLeft;
	Point downRight;
	
};

