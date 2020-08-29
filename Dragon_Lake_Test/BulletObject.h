#pragma once

#include "GameObject.h"
#include "MapArea.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"

class BulletObject: public GameObject
{
public:
	BulletObject(const MapArea& area, Point mapPosition) : GameObject(area, mapPosition) { }
	virtual ~BulletObject() { }

	virtual void moveTo(Point position) override {
		mapPosition = position;
	}

	virtual void advance(const MoveStrategy& strategy) override { }

	virtual void draw(const ScreenArea& area) const override {
		auto sprite = getSprite();
		sprite->draw(mapPosition - area.currentShift());
	}

protected:
	virtual std::shared_ptr<CSprite> getSprite() const override {
		return CSpriteFactory::instance()->getSprite("bullet");
	}

	virtual bool isValidPosition(Point p) const override {
		return true;
	}

};

