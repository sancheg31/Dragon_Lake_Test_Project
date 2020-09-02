#pragma once

#include "GameObject.h"
#include "Advanceable.h"

#include <memory>

/*
Represents bullet objects on the map
*/
class BulletObject: public GameObject, public Advanceable
{
public:
	BulletObject(std::shared_ptr<MapArea> mapArea, std::shared_ptr<ScreenArea> screenArea);
	virtual ~BulletObject();

	virtual LinearTrajectoryGenerator* setTrajectory(LinearTrajectoryGenerator* generator) override;
	virtual LinearTrajectoryGenerator* removeTrajectory() override;

	virtual void setPosition(Point position) override;
	virtual void move(Point position) override;
	virtual void advance() override; 

	virtual void draw() const override;
	virtual Point mapPosition() const override;
	virtual Point screenPosition() const override;
	virtual Point next() const override;

protected:

	virtual std::shared_ptr<CSprite> getSprite() const override;
	virtual bool isValidPosition(Point p) const override;

private:
	std::unique_ptr<LinearTrajectoryGenerator> trajectoryGenerator;

};

