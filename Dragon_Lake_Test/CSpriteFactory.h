#pragma once

#include <map>
#include <string>
#include <memory>

#include "CSprite.h"

class CSpriteFactory
{
public:
	
	static CSpriteFactory* instance();

	std::shared_ptr<CSprite> getSprite(std::string spriteName) const;

private:

	CSpriteFactory();

	static void initializePath();

	CSpriteFactory(const CSpriteFactory&) = delete;
	CSpriteFactory(CSpriteFactory&&) = delete;
	~CSpriteFactory() = default;

	static std::map<std::string, std::shared_ptr<CSprite>> paths;
	
};

