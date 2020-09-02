
#include "GameObjectFactory.h"

#include "EnemyObject.h"
#include "BulletObject.h"
#include "CursorObject.h"
#include "PlayerObject.h"

#include "MapArea.h"
#include "ScreenArea.h"

#include "LinearTrajectoryGenerator.h"

#include "Rectangle.h"

GameObjectFactory::GameObjectFactory(std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea): 
	mapArea(marea), screenArea(sarea) { }

EnemyObject* GameObjectFactory::createEnemyObject(Point position) const {
	auto enemy = new EnemyObject(mapArea, screenArea);
	enemy->setPosition(position);
	return enemy;
}

BulletObject* GameObjectFactory::createBulletObject(Point startPoint, Point cursorPoint) const {
	auto bullet = new BulletObject(mapArea, screenArea);
	auto trajectory = new LinearTrajectoryGenerator;
	trajectory->setSegment(startPoint, cursorPoint);
	bullet->setPosition(startPoint);
	bullet->setTrajectory(trajectory);
	return bullet;
}

PlayerObject* GameObjectFactory::createPlayerObject() const {
	auto player = new PlayerObject(mapArea, screenArea);
	player->setPosition(calculatePlayerPosition(player));
	return player;
}

CursorObject* GameObjectFactory::createCursorObject() const {
	return new CursorObject(mapArea, screenArea);
}


Point GameObjectFactory::calculatePlayerPosition(PlayerObject* object) const {
	Rectangle rect{ Point{0, 0}, screenArea->size(), VertexPosition::UP_LEFT };
	return rect.center() - (Point)object->size() / 2;
}