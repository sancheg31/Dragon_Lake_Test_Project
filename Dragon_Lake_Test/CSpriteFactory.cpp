#include "CSpriteFactory.h"

std::map<std::string, std::shared_ptr<CSprite>> CSpriteFactory::paths = {};
bool CSpriteFactory::created = false;

CSpriteFactory::CSpriteFactory() {
	if (!created) {
		initializePaths();
		created = true;
	}
}

std::shared_ptr<CSprite> CSpriteFactory::getSprite(std::string spriteName) const {
	return paths.find(spriteName)->second;
}

void CSpriteFactory::initializePaths() {
	paths.insert({ std::string("player"),	std::make_shared<CSprite>("Framework/data/avatar.jpg") });
	paths.insert({ std::string("bullet"), std::make_shared<CSprite>("Framework/data/bullet.png") });
	paths.insert({ std::string("circle"), std::make_shared<CSprite>("Framework/data/circle.tga") });
	paths.insert({ std::string("enemy"), std::make_shared<CSprite>("Framework/data/enemy.png") });
	paths.insert({ std::string("reticle"), std::make_shared<CSprite>("Framework/data/reticle.png") });
}
