#pragma once

#include "GameObject.h"

class EnemyObject : public GameObject
{
public:
	EnemyObject(std::shared_ptr<MapArea> area, Point startPosition);
	virtual ~EnemyObject();
	
	virtual void moveTo(Point position);

	virtual void draw(const ScreenArea& area) const override;

protected:
	virtual std::shared_ptr<CSprite> getSprite() const override;

	virtual bool isValidPosition(Point p) const override;
};

