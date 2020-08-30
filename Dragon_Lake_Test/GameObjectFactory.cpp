
#include "GameObjectFactory.h"

#include "EnemyObject.h"
#include "BulletObject.h"
#include "CursorObject.h"
#include "PlayerObject.h"

#include "SegmentPixelEngine.h"

GameObjectFactory::GameObjectFactory(std::shared_ptr<MapArea> area) : mapArea(area) { }

EnemyObject* GameObjectFactory::createEnemyObject(Point startPosition, Point playerPosition) const {
	auto enemy = new EnemyObject(mapArea, startPosition);
	return enemy;
}

BulletObject* GameObjectFactory::createBulletObject(Point startPosition, Point cursorPosition) const {
	auto bullet = new BulletObject(mapArea, startPosition);
	return bullet;
}

PlayerObject* GameObjectFactory::createPlayerObject(Point startPosition) const {
	return new PlayerObject(mapArea, startPosition);
}

CursorObject* GameObjectFactory::createCursorObject() const {
	return new CursorObject(mapArea, { -1, -1 });
}