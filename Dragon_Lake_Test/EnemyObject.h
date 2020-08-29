#pragma once

#include "GameObject.h"

#include "CSpriteFactory.h"
#include "Utility.h"
#include "ScreenArea.h"

class EnemyObject : public GameObject
{
public:
	EnemyObject(const MapArea& area, Point startPosition) : GameObject(area, startPosition) { }
	virtual ~EnemyObject() { }
	
	virtual void moveTo(Point position) {
		if (isValidPosition(position))
			mapPosition = position;
	}

	virtual void draw(const ScreenArea& area) const override {
		auto sprite = getSprite();
		sprite->draw(mapPosition - area.currentShift());
	}

	virtual void advance(const MoveStrategy&) override { }

protected:
	virtual std::shared_ptr<CSprite> getSprite() const override {
		return CSpriteFactory::instance()->getSprite("enemy");
	}

	virtual bool isValidPosition(Point p) const override {
		auto [width, height] = mapArea.size();
		auto [objw, objh] = size();
		return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
	}
};

