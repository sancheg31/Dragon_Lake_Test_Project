#pragma once

#include "GameObject.h"
#include "Utility.h"


/*
Represents cursor object on the map.
Introduced for consistency and common approach.
*/
class CursorObject: public GameObject
{
public:
	CursorObject(std::shared_ptr<MapArea> mapArea, std::shared_ptr<ScreenArea> screenArea);
	virtual ~CursorObject();

	virtual void move(Point position) override;
	virtual void draw() const override;
	virtual void setPosition(Point p) override;

	virtual Point mapPosition() const override;
	virtual Point screenPosition() const override;

protected:
	virtual std::shared_ptr<CSprite> getSprite() const override;
	virtual bool isValidPosition(Point p) const override;
};

