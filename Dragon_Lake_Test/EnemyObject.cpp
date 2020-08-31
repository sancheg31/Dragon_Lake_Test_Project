
#include "EnemyObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "MapArea.h"

#include "Utility.h"

EnemyObject::EnemyObject(std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea) :
	GameObject(marea, sarea) { }

EnemyObject::~EnemyObject() { }


void EnemyObject::setPosition(Point pos) {
	if (isValidPosition(pos))
		position = pos;
}

 void EnemyObject::move(Point pos) {
	 if (isValidPosition(position + pos))
		 position = position + pos;
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

std::shared_ptr<CSprite> EnemyObject::getSprite() const {
	return spriteCreator->getSprite("enemy");
}

bool EnemyObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}
