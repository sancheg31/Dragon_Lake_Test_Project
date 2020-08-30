#pragma once

#include "GameObject.h"
#include "Utility.h"

class CursorObject: public GameObject
{
public:
	CursorObject(std::shared_ptr<MapArea> area, Point startPosition);
	virtual ~CursorObject();

	virtual void moveTo(Point position) override;

	virtual void draw(const ScreenArea& area) const override;

protected:
	virtual std::shared_ptr<CSprite> getSprite() const override;
	virtual bool isValidPosition(Point p) const;
};

