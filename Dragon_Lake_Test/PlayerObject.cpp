
#include "PlayerObject.h"

#include "CSprite.h"
#include "CSpriteFactory.h"
#include "ScreenArea.h"
#include "MapArea.h"

PlayerObject::PlayerObject(std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea) : GameObject(marea, sarea) { }

PlayerObject::~PlayerObject() { }

void PlayerObject::setPosition(Point pos) {
	if (isValidPosition(pos)) {
		position = pos;
		screenArea->calculateScreenShift(mapArea, this);
	}
}

void PlayerObject::move(Point pos) {
	if (isValidPosition(position + pos)) {
		position = position + pos;
		screenArea->calculateScreenShift(mapArea, this);
	}
}

void PlayerObject::draw() const {
	auto sprite = getSprite();
	sprite->draw(screenPosition());
}

Point PlayerObject::mapPosition() const {
	return position;
}

Point PlayerObject::screenPosition() const {
	return position - screenArea->currentShift();
}

bool PlayerObject::isValidPosition(Point p) const {
	auto [width, height] = mapArea->size();
	auto [objw, objh] = size();
	return (p.x >= 0 && p.y >= 0 && p.x <= width - objw && p.y <= height - objh);
}

std::shared_ptr<CSprite> PlayerObject::getSprite() const {
	return spriteCreator->getSprite("player");
}

void PlayerObject::moveRight() {
	move(Point{ 10, 0 });
}

void PlayerObject::moveLeft() {
	move(Point{ -10, 0 });
}

void PlayerObject::moveUp() {
	move(Point{ 0, -10 });
}

void PlayerObject::moveDown() {
	move(Point{ 0, 10 });
}


