#pragma once

#include "GameObject.h"

#include "CSpriteFactory.h"
#include "ScreenArea.h"

class PlayerObject: public GameObject
{
public:
	PlayerObject(Point startPosition) : GameObject(startPosition) { }

	virtual void draw(const ScreenArea& area) const override {
		auto sprite = getSprite();
		sprite->draw(mapPosition - area.calculateScreenShift(*this));
	}

	virtual void advance(const MoveStrategy&) override { }

protected:

	virtual std::shared_ptr<CSprite> getSprite() const override {
		return CSpriteFactory::instance()->getSprite("player");
	}
};

