
#include "CursorObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"

CursorObject::CursorObject(std::shared_ptr<MapArea> area, Point startPosition) : GameObject(area, startPosition) { }

CursorObject::~CursorObject() { }

void CursorObject::moveTo(Point position) {
	mapPosition = position;
}

void CursorObject::draw(const ScreenArea& area) const {
	if (isValidPosition(mapPosition)) {
		auto sprite = getSprite();
		sprite->draw(mapPosition);
	}
}

std::shared_ptr<CSprite> CursorObject::getSprite() const {
	return spriteCreator->getSprite("reticle");
}

bool CursorObject::isValidPosition(Point p) const {
	return (mapPosition.x >= 0 && mapPosition.y >= 0);
}
