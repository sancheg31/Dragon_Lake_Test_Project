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

class MyFramework : public Framework 
{
public:

	MyFramework(GameObjectFactory* objectFactory, std::shared_ptr<MapArea> mapArea, ScreenArea screenArea, int enemy, int ammo);

	virtual void PreInit(int& width, int& height, bool& fullscreen);

	virtual bool Init();

	virtual void Close();

	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);
private:

	GameObjectFactory* objectFactory;
	std::shared_ptr<MapArea> mapArea;
	ScreenArea screenArea;
	PlayerObject* playerObject;
	CursorObject* cursorObject;

	int enemyCount;
	int ammoAmount;

	std::list<EnemyObject*> enemyObjects;
	std::list<BulletObject*> bulletObjects;
};



