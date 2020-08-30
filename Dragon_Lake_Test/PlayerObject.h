#pragma once

#include "GameObject.h"

class PlayerObject: public GameObject
{
public:
	PlayerObject(std::shared_ptr<MapArea> area, Point startPosition);
	virtual ~PlayerObject();

	virtual void moveTo(Point position) override;

	virtual void draw(const ScreenArea& area) const override;

protected:

	virtual std::shared_ptr<CSprite> getSprite() const override;

	virtual bool isValidPosition(Point p) const override;

};

