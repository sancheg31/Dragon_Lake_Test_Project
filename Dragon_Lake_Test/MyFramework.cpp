
#include "MyFramework.h"

#include <iostream>
#include <numeric>
#include <algorithm>

#include "PlayerObject.h"
#include "BulletObject.h"
#include "EnemyObject.h"
#include "CursorObject.h"

#include "ScreenArea.h"
#include "MapArea.h"

#include "EnemySpawner.h"
#include "EnemyAdvancer.h"

#include "GameObjectFactory.h"
#include "CSpriteFactory.h"

#include "Rectangle.h"

#include "CSprite.h"

MyFramework::MyFramework(std::shared_ptr<GameObjectFactory> factory, std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea, int enemy, int ammo) : 
					objectFactory(factory), mapArea(marea), screenArea(sarea), bulletObjects(ammo), enemyCount(enemy) {  }

void MyFramework::PreInit(int& width, int& height, bool& fullscreen) {
	auto [width_, height_] = screenArea->size();
	width = width_;
	height = height_;
	fullscreen = false;
}

bool MyFramework::Init() {
	CSpriteFactory::loadResources();

	playerObject = objectFactory->createPlayerObject();
	cursorObject = objectFactory->createCursorObject();
	
	enemySpawner = new EnemySpawner(objectFactory, mapArea->size() - CSpriteFactory::spriteSize("enemy"));
	enemySpawner->addProhibitZone(playerObject, 4);

	//enemyObjects.push_back(objectFactory->createEnemyObject(Point{ 20, 20 }, playerObject));
	//enemyObjects.push_back(objectFactory->createEnemyObject(Point{ 56, 20 }, playerObject));
	
	enemyObjects = enemySpawner->generate(playerObject, enemyCount);

	showCursor(false);
	/*
	std::cout << playerObject->mapPosition().x << " " << playerObject->mapPosition().y << '\n';
	std::cout << screenArea->currentShift().x << " " << screenArea->currentShift().y << '\n';
	*/
	return true;
}

void MyFramework::Close() {
	delete enemySpawner;
	delete playerObject;
	delete cursorObject;

	CSpriteFactory::releaseResources();
	bulletObjects.clear();

	for (auto& enemy : enemyObjects)
		delete enemy;
	enemyObjects.clear();
}

void MyFramework::restart() {
	Close();
	Init();
}


bool MyFramework::Tick() {

	static int ticks = 0;
	++ticks;

	drawTestBackground();
	Rectangle playerRect{ playerObject };
	
	//bullet-enemy collide
	//TODO
	for (auto iter = bulletObjects.begin(); iter != bulletObjects.end(); ) {
		Rectangle bulletRect{ *iter };
		bool isCollided = false;
		for (auto iter2 = enemyObjects.begin(); iter2 != enemyObjects.end(); ) {
			Rectangle enemyRect{ *iter2 };
			if (bulletRect.isCollide(enemyRect) || enemyRect.isCollide(bulletRect)) {
				isCollided = true;
				delete *iter2;
				iter2 = enemyObjects.erase(iter2);
			}
			else {
				++iter2;
			}
		}

		if (isCollided) {
			delete *iter;
			iter = bulletObjects.erase(iter);
		}
		else {
			++iter;
		}
	}

	//game restarts
	for (auto& enemy : enemyObjects) {
		Rectangle enemyRect{ enemy };
		if (playerRect.isCollide(enemyRect)) {
			restart();
			return false;
		}
	}

	if (ticks == 20) {
		EnemyAdvancer* advancer = new EnemyAdvancer(playerObject, enemyObjects);
		advancer->advance();
		delete advancer;
	}

	for (auto& enemy : enemyObjects) {
		enemy->draw();
	}

	for (auto& bullet : bulletObjects) {
		bullet->advance();
		bullet->draw();
	}
	playerObject->draw();
	cursorObject->draw();

	if (ticks == 20) {
		ticks = 0;
	}

	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	cursorObject->setPosition(Point{ x, y });
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {

	if (!isReleased) {

		auto bulletSize = (Point)CSpriteFactory::spriteSize("bullet");

		Point startPoint = centerPoint(playerObject) - bulletSize / 2;
		Point cursorPoint = centerPoint(cursorObject) - bulletSize / 2;

		auto bullet = objectFactory->createBulletObject(startPoint, cursorPoint);
		bulletObjects.addBullet(bullet);
	
	}
}

void MyFramework::onKeyPressed(FRKey k) {
	switch (k) {
	case FRKey::LEFT:
		playerObject->moveLeft();
		break;
	case FRKey::RIGHT:
		playerObject->moveRight();
		break;
	case FRKey::UP:
		playerObject->moveUp();
		break;
	case FRKey::DOWN:
		playerObject->moveDown();
		break;
	}

	for (auto& enemy : enemyObjects) {
		auto traj = enemy->removeTrajectory();
		traj->setSegment(enemy->mapPosition(), centerPoint(playerObject));
		enemy->setTrajectory(traj);
	}
}

void MyFramework::onKeyReleased(FRKey k) { }
