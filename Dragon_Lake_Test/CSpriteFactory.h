#pragma once

#include <map>
#include <string>
#include <memory>

class CSprite;

struct Size;

class CSpriteFactory
{
public:

	CSpriteFactory() = default;
	CSpriteFactory(const CSpriteFactory&) = default;
	CSpriteFactory(CSpriteFactory&&) = default;
	~CSpriteFactory() = default;

	std::shared_ptr<CSprite> getSprite(const std::string& key) const;
	void addSprite(const std::string& key, const char* path);
	
	static Size spriteSize(const std::string& key);

	static bool loadResources();
	static void releaseResources();

private:

	static std::map<std::string, std::shared_ptr<CSprite>> paths;
	static bool loaded;
};

