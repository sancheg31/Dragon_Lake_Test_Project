#pragma once

#include <map>
#include <string>
#include <memory>

#include "CSprite.h"

class CSpriteFactory
{
public:

	CSpriteFactory() = default;
	CSpriteFactory(const CSpriteFactory&) = default;
	CSpriteFactory(CSpriteFactory&&) = default;
	~CSpriteFactory() = default;

	std::shared_ptr<CSprite> getSprite(std::string spriteName) const;
	void addSprite(const std::string& key, const char* path);


private:

	static void initializePaths();

	static std::map<std::string, std::shared_ptr<CSprite>> paths;
	static bool created;
};

