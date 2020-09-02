
#include "GameEngine.h"

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
#include "EnemyAdvancePolicy.h"

#include "GameObjectFactory.h"
#include "CSpriteFactory.h"

#include "LinearTrajectoryGenerator.h"

#include "Rectangle.h"

#include "CSprite.h"

GameEngine::GameEngine(std::shared_ptr<GameObjectFactory> factory, 
						std::shared_ptr<MapArea> marea, 
						std::shared_ptr<ScreenArea> sarea, 
						int enemy, int ammo, int ticks) : 
objectFactory(factory), mapArea(marea), screenArea(sarea), bulletObjects(ammo), enemyCount(enemy), ticksCount(ticks) {  }

void GameEngine::PreInit(int& width, int& height, bool& fullscreen) {
	auto [width_, height_] = screenArea->size();
	width = width_;
	height = height_;
	fullscreen = false;
}

bool GameEngine::Init() {
	CSpriteFactory::loadResources();

	playerObject = objectFactory->createPlayerObject();
	cursorObject = objectFactory->createCursorObject();
	
	enemySpawner = new EnemySpawner(objectFactory, mapArea->size() - CSpriteFactory::spriteSize("enemy"));
	enemySpawner->addProhibitZone(playerObject, 4);
	enemyObjects = enemySpawner->generate(playerObject, enemyCount);

	advancePolicy = new EnemyAdvancePolicy(playerObject, ticksCount);

	showCursor(false);

	return true;
}

void GameEngine::Close() {
	delete enemySpawner;
	delete advancePolicy;

	delete playerObject;
	delete cursorObject;

	CSpriteFactory::releaseResources();
	bulletObjects.clear();
	enemyObjects.clear();
}

void GameEngine::restart() {
	Close();
	Init();
}


bool GameEngine::Tick() {

	drawTestBackground();
	Rectangle playerRect{ playerObject };
	
	//bullet-enemy collide
	for (auto iter = bulletObjects.begin(); iter != bulletObjects.end(); ) {
		Rectangle bulletRect{ *iter };
		bool isCollided = false;
		for (auto iter2 = enemyObjects.begin(); iter2 != enemyObjects.end(); ) {
			Rectangle enemyRect{ *iter2 };
			if (bulletRect.isCollide(enemyRect) || enemyRect.isCollide(bulletRect)) {
				isCollided = true;
				enemySpawner->removeProhibitZone(*iter2);
				iter2 = enemyObjects.erase(iter2);
			}
			else {
				++iter2;
			}
		}

		if (isCollided) {
			iter = bulletObjects.erase(iter);
		}
		else {
			++iter;
		}
	}

	//player-enemy collide
	for (auto& enemy : enemyObjects) {
		Rectangle enemyRect{ enemy };
		if (playerRect.isCollide(enemyRect)) {
			restart();
			return false;
		}
	}
	
	//enemy respawn
	if (enemyObjects.empty()) {
		enemyObjects = enemySpawner->generate(playerObject, enemyCount);
	}

	advancePolicy->advance(enemyObjects);

	for (auto& enemy : enemyObjects) {
		enemy->draw();
	}

	for (auto& bullet : bulletObjects) {
		bullet->advance();
		bullet->draw();
	}
	playerObject->draw();
	cursorObject->draw();

	return false;
}

void GameEngine::onMouseMove(int x, int y, int xrelative, int yrelative) {
	cursorObject->setPosition(Point{ x, y });
}

void GameEngine::onMouseButtonClick(FRMouseButton button, bool isReleased) {

	if (!isReleased && button == FRMouseButton::LEFT) {

		auto bulletSize = (Point)CSpriteFactory::spriteSize("bullet");

		Point startPoint = centerPoint(playerObject) - bulletSize / 2;
		Point cursorPoint = centerPoint(cursorObject) - bulletSize / 2;

		auto bullet = objectFactory->createBulletObject(startPoint, cursorPoint);
		bulletObjects.addBullet(bullet);
	
	}
}

void GameEngine::onKeyPressed(FRKey k) {
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

void GameEngine::onKeyReleased(FRKey k) { }
