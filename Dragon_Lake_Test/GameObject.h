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

	GameObject(std::shared_ptr<MapArea> area, Point position);
	GameObject(const GameObject&) = default;
	GameObject(GameObject&&) = default;
	GameObject& operator=(const GameObject&) = default;
	GameObject& operator=(GameObject&&) = default;
	virtual ~GameObject() = default;

	virtual void moveTo(Point position) = 0;
	virtual void draw(const ScreenArea& area) const = 0;

	Point position() const;
	Size size() const;

	static void setSpriteCreator(CSpriteFactory* factory);

protected:
	virtual std::shared_ptr<CSprite> getSprite() const = 0;
	virtual bool isValidPosition(Point p) const = 0;

	static std::unique_ptr<CSpriteFactory> spriteCreator;

	std::shared_ptr<MapArea> mapArea;
	Point mapPosition{ 0, 0 };
};

