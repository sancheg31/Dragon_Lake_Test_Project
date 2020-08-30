
#include "EnemyObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "MapArea.h"

#include "Utility.h"

EnemyObject::EnemyObject(std::shared_ptr<MapArea> area, Point startPosition) : 
	GameObject(area, startPosition) { }

EnemyObject::~EnemyObject() { }

 void EnemyObject::moveTo(Point position) {
	if (isValidPosition(position))
		mapPosition = position;
}

 void EnemyObject::advance() {

 }

void EnemyObject::draw(const ScreenArea& area) const {
	auto sprite = getSprite();
	sprite->draw(mapPosition - area.currentShift());
}

std::shared_ptr<CSprite> EnemyObject::getSprite() const {
	return spriteCreator->getSprite("enemy");
}

bool EnemyObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}
