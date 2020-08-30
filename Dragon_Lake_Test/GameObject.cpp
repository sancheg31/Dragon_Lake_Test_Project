
#include "GameObject.h"

#include "MapArea.h"
#include "CSprite.h"
#include "CSpriteFactory.h"


std::unique_ptr<CSpriteFactory> GameObject::spriteCreator = nullptr;

GameObject::GameObject(std::shared_ptr<MapArea> area, Point position) : mapArea(area), mapPosition(position) { }

Point GameObject::position() const {
	return mapPosition;
}

Size GameObject::size() const {
	return getSprite()->size();
}

void GameObject::setSpriteCreator(CSpriteFactory* factory) {
	spriteCreator.reset(factory);
}

