#pragma once

#include "Utility.h"

#include <memory>

class ScreenArea;
class MapArea;

class CSprite;
class CSpriteFactory;

class GameObject
{
public:

	GameObject(std::shared_ptr<MapArea> mapArea, std::shared_ptr<ScreenArea> screenArea);
	GameObject(const GameObject&) = default;
	GameObject(GameObject&&) = default;
	GameObject& operator=(const GameObject&) = default;
	GameObject& operator=(GameObject&&) = default;
	virtual ~GameObject() = default;

	virtual void move(Point position) = 0;
	virtual void draw() const = 0;
	virtual void setPosition(Point p) = 0;

	virtual Point mapPosition() const = 0;
	virtual Point screenPosition() const = 0;

	Size size() const;

	static void setSpriteCreator(CSpriteFactory* factory);

protected:
	virtual std::shared_ptr<CSprite> getSprite() const = 0;
	virtual bool isValidPosition(Point p) const = 0;

	static std::unique_ptr<CSpriteFactory> spriteCreator;

	std::shared_ptr<MapArea> mapArea;
	std::shared_ptr<ScreenArea> screenArea;
	Point position{ 0, 0 };
};

