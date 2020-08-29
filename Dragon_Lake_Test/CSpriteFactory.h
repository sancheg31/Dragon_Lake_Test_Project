#pragma once

#include <map>
#include <string>

#include "CSprite.h"

class CSpriteFactory
{
public:
	
	static CSpriteFactory* instance() {
		static CSpriteFactory* instance_ = new CSpriteFactory();
		return instance_;
	}

	CSprite* createSprite(std::string spriteName) {
		return new CSprite(paths.find(spriteName)->second);
	}

private:

	CSpriteFactory() { }

	CSpriteFactory(const CSpriteFactory&) = delete;
	CSpriteFactory(CSpriteFactory&&) = delete;
	~CSpriteFactory() = default;

	static std::map<std::string, char*> paths;
	
};

std::map<std::string, char*> CSpriteFactory::paths	{ 	
														{std::string("player"),	(char*)"/Framework/data/avatar.jpg"},
														{std::string("bullet"), (char*)"/Framework/data/bullet.png" },
														{std::string("circle"), (char*)"/Framework/data/circle.tga" },
														{std::string("bullet"), (char*)"/Framework/data/enemy.png" },
														{std::string("bullet"), (char*)"/Framework/data/reticle.png" } 
													};

