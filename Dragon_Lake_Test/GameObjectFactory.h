#pragma once

class GameObject;
class PlayerObject;
class CursorObject;
class BulletObject;
class EnemyObject;

class MapArea;
class ScreenArea;

#include <memory>

class GameObjectFactory
{
public:
	GameObjectFactory(std::shared_ptr<MapArea> mapArea, std::shared_ptr<ScreenArea> screenArea);

	EnemyObject* createEnemyObject() const;
	BulletObject* createBulletObject() const;
	PlayerObject* createPlayerObject() const; 
	CursorObject* createCursorObject() const;

private:
	std::shared_ptr<MapArea> mapArea;
	std::shared_ptr<ScreenArea> screenArea;
};

