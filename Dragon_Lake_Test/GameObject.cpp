
#include "GameObject.h"

#include "MapArea.h"
#include "CSpriteFactory.h"


std::unique_ptr<CSpriteFactory> spriteCreator = std::unique_ptr<CSpriteFactory>{ new CSpriteFactory() };

GameObject::GameObject(std::shared_ptr<MapArea> area, Point position) : mapArea(area), mapPosition(position) { }

Point GameObject::position() const {
	return mapPosition;
}

Size GameObject::size() const {
	return getSprite()->size();
}
