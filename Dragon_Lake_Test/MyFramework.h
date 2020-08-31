#pragma once

#include <list>
#include <memory>

#include <Framework.h>

#include "Utility.h"

#include "ScreenArea.h"
#include "MapArea.h"

#include "PlayerObject.h"
#include "EnemyObject.h"
#include "CursorObject.h"
#include "BulletObject.h"
#include "GameObjectFactory.h"

#include "LinearTrajectoryGenerator.h"

class MyFramework : public Framework 
{
public:

	MyFramework(GameObjectFactory* objectFactory, std::shared_ptr<MapArea> mapArea, std::shared_ptr<ScreenArea> screenArea, int enemy, int ammo);

	virtual void PreInit(int& width, int& height, bool& fullscreen);

	virtual bool Init();

	virtual void Close();

	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);

	Point direct(Point start, Point end);
private:

	GameObjectFactory* objectFactory;
	std::shared_ptr<MapArea> mapArea;
	std::shared_ptr<ScreenArea> screenArea;
	PlayerObject* playerObject;
	CursorObject* cursorObject;
	LinearTrajectoryGenerator* trajectory;

	int enemyCount;
	int ammoAmount;

	std::list<EnemyObject*> enemyObjects;
	
	BulletObject* bullet;
};



