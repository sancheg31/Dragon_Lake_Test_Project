
#include "EnemyObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "MapArea.h"

#include "LinearTrajectoryGenerator.h"

#include "Utility.h"

EnemyObject::EnemyObject(std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea) :
	GameObject(marea, sarea) { }

EnemyObject::~EnemyObject() { 
	trajectoryGenerator.reset(nullptr);
}

LinearTrajectoryGenerator* EnemyObject::setTrajectory(LinearTrajectoryGenerator* generator) {
	auto gen = trajectoryGenerator.release();
	trajectoryGenerator.reset(generator);
	return gen;
}

LinearTrajectoryGenerator* EnemyObject::removeTrajectory() {
	return trajectoryGenerator.release();
}

void EnemyObject::setPosition(Point pos) {
	if (isValidPosition(pos))
		position = pos;
}

 void EnemyObject::move(Point pos) {
	 if (isValidPosition(position + pos))
		 position = position + pos;
}

 void EnemyObject::advance() {
	 if (trajectoryGenerator && ticksCount == 20) {
		 ticksCount = 0;
		 setPosition(trajectoryGenerator->advance());
	 }
	 else {
		 ++ticksCount;
	 }
 }

void EnemyObject::draw() const {
	auto sprite = getSprite();
	sprite->draw(screenPosition());
}

Point EnemyObject::screenPosition() const {
	return position - screenArea->currentShift();
}

Point EnemyObject::mapPosition() const {
	return position;
}

Point EnemyObject::next() const {
	if (trajectoryGenerator)
		return trajectoryGenerator->next();
	return mapPosition();
}

std::shared_ptr<CSprite> EnemyObject::getSprite() const {
	return spriteCreator->getSprite("enemy");
}

bool EnemyObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}
