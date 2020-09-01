
#include "GameObject.h"

#include "MapArea.h"
#include "CSprite.h"
#include "CSpriteFactory.h"


std::unique_ptr<CSpriteFactory> GameObject::spriteCreator = nullptr;

GameObject::GameObject(std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea) 
	: mapArea(marea), screenArea(sarea) { }

Size GameObject::size() const {
	return getSprite()->size();
}

/*static*/ void GameObject::setSpriteCreator(CSpriteFactory* factory) {
	spriteCreator.reset(factory);
}



