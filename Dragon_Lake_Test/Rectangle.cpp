#include "Rectangle.h"

#include <utility>

struct Rectangle::Projection
{
	int first;
	int second;

	bool isValueBetween(int val) {
		auto [less, bigger] = (first < second) ? std::pair{ first, second } : std::pair{ second, first };
		return val >= less && val <= bigger;
	}
};

Rectangle::Rectangle(Point p, Size dim, VertexPosition position) {
	switch (position) {
	case VertexPosition::UP_RIGHT:
		constructFromUpperLeft(Point{ p.x - dim.width, p.y }, dim);
		break;
	case VertexPosition::UP_LEFT:
		constructFromUpperLeft(p, dim);
		break;
	case VertexPosition::DOWN_LEFT:
		constructFromUpperLeft(Point{ p.x, p.y - dim.height }, dim);
		break;
	case VertexPosition::DOWN_RIGHT:
		constructFromUpperLeft(Point{ p.x - dim.width, p.y - dim.height }, dim);
		break;
	}
}
void Rectangle::constructFromUpperLeft(Point p, Size dimensions) {
	upLeft_ = p;
	downRight_ = Point{ p.x + dimensions.width, p.y + dimensions.height };
}

bool Rectangle::isContained(Point p) const {
	return (p.x >= upLeft_.x && p.x <= downRight_.x && p.y >= upLeft_.y && p.y <= downRight_.y);
}

bool Rectangle::isCollide(Rectangle rect) const {

	Projection x{ upLeft_.x, downRight_.x };
	Projection y{ upLeft_.y, downRight_.y };
	Projection xrect{ rect.upLeft_.x, rect.downRight_.x };
	Projection yrect{ rect.upLeft_.y, rect.downRight_.y };

	bool interceptsX = x.isValueBetween(xrect.first) || x.isValueBetween(xrect.second);
	bool interceptsY = y.isValueBetween(yrect.first) || y.isValueBetween(yrect.second);
	return interceptsX && interceptsY;
}

Point Rectangle::center() const {
	Point dimensions = downRight_ - upLeft_;
	return (upLeft_ + (dimensions / 2));
}

Point Rectangle::upRight() const {
	return Point{ downRight_.x, upLeft_.y };
}

Point Rectangle::upLeft() const {
	return upLeft_;
}

Point Rectangle::downRight() const {
	return downRight_;
}

Point Rectangle::downLeft() const {
	return Point{ upLeft_.x, downRight_.y };
}
