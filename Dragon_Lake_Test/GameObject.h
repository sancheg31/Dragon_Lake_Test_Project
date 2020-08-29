#pragma once

#include "Utility.h"
#include "CSprite.h"

#include <memory>

class ScreenArea;
class MoveStrategy;

class GameObject
{
public:

	GameObject(Point position) : mapPosition(position) { }

	void moveTo(Point position) {
		mapPosition = position;
	}

	virtual void draw(const ScreenArea& area) const = 0;
	virtual void advance(const MoveStrategy& strategy) = 0;


	Point position() const {
		return mapPosition;
	}

	Size size() const {
		return getSprite()->size();
	}

protected:
	virtual std::shared_ptr<CSprite> getSprite() const = 0;
	Point mapPosition{ 0, 0 };
};

