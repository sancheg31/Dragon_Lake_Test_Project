#pragma once

#include "GameObject.h"

#include "Utility.h"
#include "CSpriteFactory.h"

class CursorObject: public GameObject
{
public:
	CursorObject(const MapArea& area, Point startPosition): GameObject(area, startPosition) { }
	virtual ~CursorObject() { }

	virtual void moveTo(Point position) override  {
		mapPosition = position;
	}

	virtual void advance(const MoveStrategy&) override { }

	virtual void draw(const ScreenArea& area) const override {
		if (isValidPosition(mapPosition)) {
			auto sprite = getSprite();
			sprite->draw(mapPosition);
		}
	}

protected:
	virtual std::shared_ptr<CSprite> getSprite() const override {
		return CSpriteFactory::instance()->getSprite("reticle");
	}
	virtual bool isValidPosition(Point p) const {
		return (mapPosition.x >= 0 && mapPosition.y >= 0);
	}
};

