#pragma once

#include <map>
#include <string>
#include <memory>

#include "CSprite.h"

class CSpriteFactory
{
public:
	
	static CSpriteFactory* instance() {
		static CSpriteFactory* instance_ = new CSpriteFactory();
		return instance_;
	}

	std::shared_ptr<CSprite> getSprite(std::string spriteName) const {
		return paths.find(spriteName)->second;
	}

private:

	CSpriteFactory() {
		initializePath();
	}

	void initializePath() {
		paths.insert({ std::string("player"),	std::make_shared<CSprite>("/Framework/data/avatar.jpg") });
		paths.insert({ std::string("bullet"), std::make_shared<CSprite>("/Framework/data/bullet.png") });
		paths.insert({ std::string("circle"), std::make_shared<CSprite>("/Framework/data/circle.tga") });
		paths.insert({ std::string("enemy"), std::make_shared<CSprite>("/Framework/data/enemy.png") });
		paths.insert({ std::string("reticle"), std::make_shared<CSprite>("/Framework/data/reticle.png") });
	}

	CSpriteFactory(const CSpriteFactory&) = delete;
	CSpriteFactory(CSpriteFactory&&) = delete;
	~CSpriteFactory() = default;

	static std::map<std::string, std::shared_ptr<CSprite>> paths;
	
};

