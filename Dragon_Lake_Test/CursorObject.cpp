
#include "CursorObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "MapArea.h"	

CursorObject::CursorObject(std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea) : GameObject(marea, sarea) { }

CursorObject::~CursorObject() { }

void CursorObject::move(Point pos) {
	if (isValidPosition(position + pos))
		position = position + pos;
}

void CursorObject::setPosition(Point pos) {
	if (isValidPosition(pos))
		position = pos;
}

void CursorObject::draw() const {
	auto sprite = getSprite();
	sprite->draw(screenPosition());
}

Point CursorObject::mapPosition() const {
	return position + screenArea->currentShift();
}

Point CursorObject::screenPosition() const {
	return position;
}

std::shared_ptr<CSprite> CursorObject::getSprite() const {
	return spriteCreator->getSprite("reticle");
}

bool CursorObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}
