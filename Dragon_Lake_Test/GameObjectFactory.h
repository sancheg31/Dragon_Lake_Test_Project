#pragma once

class GameObject;
class PlayerObject;
class CursorObject;
class BulletObject;
class EnemyObject;

class MapArea;
struct Point;

#include <memory>

#include "MapArea.h"

class GameObjectFactory
{
public:
	GameObjectFactory(std::shared_ptr<MapArea> area);

	EnemyObject* createEnemyObject(Point startPosition, Point playerPosition) const;
	BulletObject* createBulletObject(Point startPosition, Point cursorPosition) const;
	PlayerObject* createPlayerObject(Point startPosition) const; 
	CursorObject* createCursorObject() const;

private:
	std::shared_ptr<MapArea> mapArea;
};

