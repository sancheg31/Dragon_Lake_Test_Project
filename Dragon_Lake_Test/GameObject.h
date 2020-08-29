#pragma once

#include "Utility.h"
#include "CSprite.h"
#include "MapArea.h"

#include <memory>

class ScreenArea;
class MoveStrategy;

class GameObject
{
public:

	GameObject(const MapArea& area, Point position) : mapArea(area), mapPosition(position) { }
	virtual ~GameObject() { }

	virtual void moveTo(Point position) = 0;
	virtual void advance(const MoveStrategy& strategy) = 0;
	virtual void draw(const ScreenArea& area) const = 0;


	Point position() const {
		return mapPosition;
	}

	Size size() const {
		return getSprite()->size();
	}

protected:
	virtual std::shared_ptr<CSprite> getSprite() const = 0;
	virtual bool isValidPosition(Point p) const = 0;

	const MapArea& mapArea;
	Point mapPosition{ 0, 0 };
};

