
#include "BulletObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "Utility.h"
#include "MapArea.h"

#include "LinearTrajectoryGenerator.h"

BulletObject::BulletObject(std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea)
	: GameObject(marea, sarea) { }

BulletObject::~BulletObject() { }

LinearTrajectoryGenerator* BulletObject::setTrajectory(LinearTrajectoryGenerator* generator) {
	auto gen = trajectoryGenerator.release();
	trajectoryGenerator.reset(generator);
	return gen;
}

LinearTrajectoryGenerator* BulletObject::removeTrajectory() {
	return trajectoryGenerator.release();
}

void BulletObject::setPosition(Point pos) {
	if (isValidPosition(pos))
		position = pos;
}

void BulletObject::move(Point pos) {
	if (isValidPosition(position + pos))
		position = position + pos;
}

void BulletObject::advance() {
	if (trajectoryGenerator) {
		setPosition(trajectoryGenerator->advance());
	}
}

void BulletObject::draw() const {
	auto sprite = getSprite();
	sprite->draw(screenPosition());
}

Point BulletObject::screenPosition() const {
	return position - screenArea->currentShift();
}

Point BulletObject::mapPosition() const {
	return position;
}

Point BulletObject::next() const {
	return trajectoryGenerator->next();
}

std::shared_ptr<CSprite> BulletObject::getSprite() const {
	return spriteCreator->getSprite("bullet");
}

bool BulletObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}
