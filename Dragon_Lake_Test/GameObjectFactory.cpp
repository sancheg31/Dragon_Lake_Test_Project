
#include "GameObjectFactory.h"

#include "EnemyObject.h"
#include "BulletObject.h"
#include "CursorObject.h"
#include "PlayerObject.h"

#include "MapArea.h"
#include "ScreenArea.h"

GameObjectFactory::GameObjectFactory(std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea): 
	mapArea(marea), screenArea(sarea) { }

EnemyObject* GameObjectFactory::createEnemyObject() const {
	auto enemy = new EnemyObject(mapArea, screenArea);
	return enemy;
}

BulletObject* GameObjectFactory::createBulletObject() const {
	auto bullet = new BulletObject(mapArea, screenArea);
	return bullet;
}

PlayerObject* GameObjectFactory::createPlayerObject() const {
	return new PlayerObject(mapArea, screenArea);
}

CursorObject* GameObjectFactory::createCursorObject() const {
	return new CursorObject(mapArea, screenArea);
}