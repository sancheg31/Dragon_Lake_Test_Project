#pragma once

#include "GameObject.h"

/*
Represents player on the map
*/

class PlayerObject: public GameObject
{
public:
	PlayerObject(std::shared_ptr<MapArea> mapArea, std::shared_ptr<ScreenArea> screenArea);
	virtual ~PlayerObject();

	virtual void setPosition(Point position) override;
	virtual void move(Point position) override;

	virtual void draw() const override;
	virtual Point mapPosition() const override;
	virtual Point screenPosition() const override;

	virtual void moveRight();
	virtual void moveLeft();
	virtual void moveUp();
	virtual void moveDown();

protected:

	virtual std::shared_ptr<CSprite> getSprite() const override;
	virtual bool isValidPosition(Point p) const override;

};

