
#include "CSpriteFactory.h"

#include "CSprite.h"
#include "Utility.h"

std::map<std::string, std::shared_ptr<CSprite>> CSpriteFactory::paths = {};
bool CSpriteFactory::loaded = false;

std::shared_ptr<CSprite> CSpriteFactory::getSprite(const std::string& spriteName) const {
	if (!loaded) {
		loadResources();
	}
	auto iter = paths.find(spriteName);
	if (iter == paths.end())
		return std::shared_ptr<CSprite>{ nullptr };
	return iter->second;
}

/*static*/ Size CSpriteFactory::spriteSize(const std::string& key) {
	if (!loaded) {
		loadResources();
	}
	return paths.find(key)->second->size();
}

void CSpriteFactory::addSprite(const std::string& key, const char* path) {
	paths.insert({ key, std::make_shared<CSprite>(path) });
}

/*static*/ bool CSpriteFactory::loadResources() {
	//if (loaded)
	//	return true;
	paths.insert({ std::string("player"), std::make_shared<CSprite>("Framework/data/avatar.jpg") });
	paths.insert({ std::string("bullet"), std::make_shared<CSprite>("Framework/data/bullet.png") });
	paths.insert({ std::string("circle"), std::make_shared<CSprite>("Framework/data/circle.tga") });
	paths.insert({ std::string("enemy"), std::make_shared<CSprite>("Framework/data/enemy.png") });
	paths.insert({ std::string("reticle"), std::make_shared<CSprite>("Framework/data/reticle.png") });
	loaded = true;
	return true;
}

/*static*/ void CSpriteFactory::releaseResources() {
	for (auto iter = paths.begin(); iter != paths.end(); ) {
		if (iter->second.use_count() == 1) {
			iter->second.reset();
			iter = paths.erase(iter);
		}
		else {
			++iter;
		}
	}
	loaded = false;
}