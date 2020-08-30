
#include "CursorObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "MapArea.h"	

CursorObject::CursorObject(std::shared_ptr<MapArea> area, Point startPosition) : GameObject(area, startPosition) { }

CursorObject::~CursorObject() { }

void CursorObject::moveTo(Point position) {
	mapPosition = position;
}

void CursorObject::draw(const ScreenArea& area) const {
	if (isValidPosition(mapPosition)) {
		auto sprite = getSprite();
		sprite->draw(mapPosition - area.currentShift());
	}
}

std::shared_ptr<CSprite> CursorObject::getSprite() const {
	return spriteCreator->getSprite("reticle");
}

bool CursorObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}
