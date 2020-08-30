
#include "BulletObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "Utility.h"
#include "MapArea.h"

BulletObject::BulletObject(std::shared_ptr<MapArea> area, Point mapPosition)
	: GameObject(area, mapPosition) { } 

BulletObject::~BulletObject() { }

void BulletObject::moveTo(Point position) {
	mapPosition = position;
}

void BulletObject::advance() {

}

void BulletObject::draw(const ScreenArea& area) const {
	if (isValidPosition(mapPosition)) {
		auto sprite = getSprite();
		sprite->draw(mapPosition - area.currentShift());
	}
}

std::shared_ptr<CSprite> BulletObject::getSprite() const {
	return spriteCreator->getSprite("bullet");
}

bool BulletObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}
