#pragma once

#include "GameObject.h"

struct Point;

class EnemyObject : public GameObject
{
public:
	EnemyObject(std::shared_ptr<MapArea> mapArea, std::shared_ptr<ScreenArea> screenArea);
	virtual ~EnemyObject();

	virtual void setPosition(Point position) override;
	virtual void move(Point position) override;

	virtual void draw() const override;
	virtual Point mapPosition() const override;
	virtual Point screenPosition() const override;

protected:

	virtual std::shared_ptr<CSprite> getSprite() const override;
	virtual bool isValidPosition(Point p) const override;
};

