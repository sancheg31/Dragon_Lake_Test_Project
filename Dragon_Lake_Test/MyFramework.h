#pragma once

#include <list>
#include <memory>

#include <Framework.h>

#include "BulletStorage.h"

class EnemyStorage;

class PlayerObject;
class CursorObject;
class EnemyObject;
class BulletObject;

class EnemySpawner;

class GameObjectFactory;

class MapArea;
class ScreenArea;

class MyFramework : public Framework 
{
public:

	MyFramework(std::shared_ptr<GameObjectFactory> objectFactory, 
				std::shared_ptr<MapArea> mapArea, 
				std::shared_ptr<ScreenArea> screenArea, 
				int enemy, int ammo);

	virtual void PreInit(int& width, int& height, bool& fullscreen);

	virtual bool Init();

	virtual void Close();

	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);

	void restart();

private:

	std::shared_ptr<GameObjectFactory> objectFactory;
	std::shared_ptr<MapArea> mapArea;
	std::shared_ptr<ScreenArea> screenArea;
	
	PlayerObject* playerObject;
	CursorObject* cursorObject;
	EnemySpawner* enemySpawner;

	int enemyCount;

	std::list<EnemyObject*> enemyObjects;
	BulletStorage bulletObjects;
};



