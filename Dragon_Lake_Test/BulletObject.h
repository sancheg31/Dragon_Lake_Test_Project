#pragma once

#include "GameObject.h"

class BulletObject: public GameObject
{
public:
	BulletObject(std::shared_ptr<MapArea> area, Point mapPosition);
	virtual ~BulletObject();

	virtual void moveTo(Point position) override;
	void advance();
	virtual void draw(const ScreenArea& area) const override;

protected:
	virtual std::shared_ptr<CSprite> getSprite() const override;

	virtual bool isValidPosition(Point p) const override;

};

