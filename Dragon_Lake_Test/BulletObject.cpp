
#include "BulletObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "Utility.h"

BulletObject::BulletObject(std::shared_ptr<MapArea> area, Point mapPosition)
	: GameObject(area, mapPosition) { } 

BulletObject::~BulletObject() { }

void BulletObject::moveTo(Point position) {
	mapPosition = position;
}

void BulletObject::advance() {

}

void BulletObject::draw(const ScreenArea& area) const {
	auto sprite = getSprite();
	sprite->draw(mapPosition - area.currentShift());
}

std::shared_ptr<CSprite> BulletObject::getSprite() const {
	return spriteCreator->getSprite("bullet");
}

bool BulletObject::isValidPosition(Point p) const {
	return true;
}
