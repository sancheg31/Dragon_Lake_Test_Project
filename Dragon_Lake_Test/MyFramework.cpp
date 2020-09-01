
#include "MyFramework.h"

#include <iostream>

#include "PlayerObject.h"
#include "BulletObject.h"
#include "EnemyObject.h"
#include "CursorObject.h"

#include "ScreenArea.h"
#include "MapArea.h"

#include "EnemySpawner.h"

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
	
	enemyObjects = enemySpawner->generate(playerObject, enemyCount);

	std::cout << "enemy count: " << enemyObjects.size();

	showCursor(false);

	std::cout << playerObject->mapPosition().x << " " << playerObject->mapPosition().y << '\n';
	std::cout << screenArea->currentShift().x << " " << screenArea->currentShift().y << '\n';

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

	drawTestBackground();
	Rectangle playerRect{ *playerObject };
	
	//TODO
	for (auto iter = bulletObjects.begin(); iter != bulletObjects.end(); ) {
		Rectangle bulletRect{ **iter };
		bool isCollided = false;
		for (auto iter2 = enemyObjects.begin(); iter2 != enemyObjects.end(); ) {
			Rectangle enemyRect{ **iter2 };
			if (bulletRect.isCollide(enemyRect) || enemyRect.isCollide(bulletRect)) {
				isCollided = true;
				delete *iter2;
				iter2 = enemyObjects.erase(iter2);
				std::cout << "enemies left: " << enemyObjects.size() << '\n';
			}
			else {
				++iter2;
			}
		}

		if (isCollided) {
			delete *iter;
			iter = bulletObjects.storage().erase(iter);
		}
		else {
			++iter;
		}
	}
	
	for (auto& enemy : enemyObjects) {
		Rectangle enemyRect{ *enemy };
		if (playerRect.isCollide(enemyRect)) {
			restart();
			return false;
		}
	}

	for (auto& enemy : enemyObjects) {
		enemy->advance();
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

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	cursorObject->setPosition(Point{ x, y });
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {

	if (!isReleased) {

		auto bulletSize = (Point)CSpriteFactory::spriteSize("bullet");
		Point startPoint = Rectangle{ *playerObject }.center() - bulletSize / 2;
		Point cursorPoint = Rectangle{ *cursorObject }.center() - bulletSize / 2;

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
		traj->setSegment(enemy->mapPosition(), Rectangle{ *playerObject }.center());
		enemy->setTrajectory(traj);
	}
}

void MyFramework::onKeyReleased(FRKey k) { }
