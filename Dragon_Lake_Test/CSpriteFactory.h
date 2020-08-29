#pragma once

#include <map>
#include <string>
#include <memory>

#include "CSprite.h"

class CSpriteFactory
{
public:

	CSpriteFactory();
	std::shared_ptr<CSprite> getSprite(std::string spriteName) const;

private:

	CSpriteFactory(const CSpriteFactory&) = delete;
	CSpriteFactory(CSpriteFactory&&) = delete;
	~CSpriteFactory() = default;

	static void initializePaths();

	static std::map<std::string, std::shared_ptr<CSprite>> paths;
	static bool created;
};

