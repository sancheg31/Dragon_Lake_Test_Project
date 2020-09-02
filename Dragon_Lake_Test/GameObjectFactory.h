#pragma once

class GameObject;
class PlayerObject;
class CursorObject;
class BulletObject;
class EnemyObject;

class MapArea;
class ScreenArea;

struct Point;

#include <memory>

class GameObjectFactory
{
public:
	GameObjectFactory(std::shared_ptr<MapArea> mapArea, std::shared_ptr<ScreenArea> screenArea);

	EnemyObject* createEnemyObject(Point position, GameObject* target) const;
	BulletObject* createBulletObject(Point startPosition, Point cursorPosition) const;
	PlayerObject* createPlayerObject() const; 
	CursorObject* createCursorObject() const;

private:

	Point calculatePlayerPosition(PlayerObject* object) const;

	std::shared_ptr<MapArea> mapArea;
	std::shared_ptr<ScreenArea> screenArea;
};

