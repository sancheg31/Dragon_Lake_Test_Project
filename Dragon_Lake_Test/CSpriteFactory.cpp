#include "CSpriteFactory.h"

std::map<std::string, std::shared_ptr<CSprite>> CSpriteFactory::paths = {};

CSpriteFactory* CSpriteFactory::instance() {
	static CSpriteFactory* instance_ = new CSpriteFactory();
	return instance_;
}

std::shared_ptr<CSprite> CSpriteFactory::getSprite(std::string spriteName) const {
	return paths.find(spriteName)->second;
}

CSpriteFactory::CSpriteFactory() {
	initializePath();
}

void CSpriteFactory::initializePath() {
	paths.insert({ std::string("player"),	std::make_shared<CSprite>("Framework/data/avatar.jpg") });
	paths.insert({ std::string("bullet"), std::make_shared<CSprite>("Framework/data/bullet.png") });
	paths.insert({ std::string("circle"), std::make_shared<CSprite>("Framework/data/circle.tga") });
	paths.insert({ std::string("enemy"), std::make_shared<CSprite>("Framework/data/enemy.png") });
	paths.insert({ std::string("reticle"), std::make_shared<CSprite>("Framework/data/reticle.png") });
}
