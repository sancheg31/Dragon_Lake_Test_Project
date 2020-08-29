#pragma once

#include "GameObject.h"

#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "MapArea.h"

class PlayerObject: public GameObject
{
public:
	PlayerObject(const MapArea& area, Point startPosition) : GameObject(area, startPosition) { }
	virtual ~PlayerObject() { }

	virtual void moveTo(Point position) override {
		if (isValidPosition(position))
			mapPosition = position;
	}

	virtual void draw(const ScreenArea& area) const override {
		auto sprite = getSprite();
		Point shiftedPosition = mapPosition - area.calculateScreenShift(*this);
		sprite->draw(shiftedPosition);
	}

	virtual void advance(const MoveStrategy&) override { }

protected:

	virtual std::shared_ptr<CSprite> getSprite() const override {
		return CSpriteFactory::instance()->getSprite("player");
	}

	virtual bool isValidPosition(Point p) const override {
		auto [width, height] = mapArea.size();
		auto [objw, objh] = size();
		return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
	}

};

