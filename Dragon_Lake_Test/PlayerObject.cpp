
#include "PlayerObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "MapArea.h"

PlayerObject::PlayerObject(std::shared_ptr<MapArea> area, Point startPosition) : GameObject(area, startPosition) { }

PlayerObject::~PlayerObject() { }

void PlayerObject::moveTo(Point position) {
	if (isValidPosition(position))
		mapPosition = position;
}

void PlayerObject::draw(const ScreenArea& area) const {
	auto sprite = getSprite();
	Point shiftedPosition = mapPosition - area.calculateScreenShift(*this);
	sprite->draw(shiftedPosition);
}

std::shared_ptr<CSprite> PlayerObject::getSprite() const {
	return spriteCreator->getSprite("player");
}

bool PlayerObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}
