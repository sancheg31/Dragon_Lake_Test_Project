
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
	
	enemyObjects = enemySpawner->generate(playerObject, 500);

	/*auto enemy1 = objectFactory->createEnemyObject(Point{ 20, 20 });
	auto trajectory1 = new LinearTrajectoryGenerator();
	trajectory1->setSegment(Rectangle{ *enemy1 }.center(), Rectangle{ *playerObject }.center());
	enemy1->setTrajectory(trajectory1);
	enemyObjects.push_back(enemy1);

	auto enemy2 = objectFactory->createEnemyObject(Point{ 22, 22 });
	auto trajectory2 = new LinearTrajectoryGenerator();
	trajectory2->setSegment(Rectangle{ *enemy2 }.center(), Rectangle{ *playerObject }.center());
	enemy2->setTrajectory(trajectory2);
	enemyObjects.push_back(enemy2);*/

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

#include <cmath>
double distance(Point p1, Point p2) {
	auto p = p1 - p2;
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool MyFramework::Tick() {

	static int ticks = 0;
	++ticks;

	drawTestBackground();
	Rectangle playerRect{ *playerObject };
	
	//bullet-enemy collide
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
			iter = bulletObjects.erase(iter);
		}
		else {
			++iter;
		}
	}

	//game restarts
	for (auto& enemy : enemyObjects) {
		Rectangle enemyRect{ *enemy };
		if (playerRect.isCollide(enemyRect)) {
			restart();
			return false;
		}
	}

	//chooses which bullet advances and which halts
	std::list<std::pair<EnemyObject*, bool>> advancedList;

	std::transform(enemyObjects.begin(), enemyObjects.end(), std::back_inserter(advancedList), [](auto enemy) {
		return std::pair{ enemy, true };
	});

	for (auto iter1 = advancedList.begin(); iter1 != advancedList.end(); ++iter1) {
		EnemyObject* enemy1 = iter1->first;
		Rectangle rect1{ enemy1->next(), enemy1->size(), VertexPosition::UP_LEFT };

		std::list<EnemyObject*> collideList{ enemy1 };

		{
			auto iter2 = iter1;
			++iter2;
			for (; iter2 != advancedList.end(); ++iter2) {
				EnemyObject* enemy2 = iter2->first;
				Rectangle rect2{ enemy2->next(), enemy2->size(), VertexPosition::UP_LEFT };

				if (rect2.isCollide(rect1)) {
					collideList.push_back(enemy2);
				}
			}
		}

		if (collideList.size() > 1) {
			if (ticks >= 20)
				std::cout << "Collide\n";
			EnemyObject* obj = *collideList.begin();
			double dist = distance(Rectangle{ obj->next(), obj->size(), VertexPosition::UP_LEFT }.center(), 
									Rectangle{ *playerObject }.center());

			//find object that moves
			for (auto iter = collideList.begin(); iter != collideList.end(); ++iter) {
				auto objj = *iter;
				Rectangle rect{ objj->next(), objj->size(), VertexPosition::UP_LEFT };
				double temp = distance(rect.center(), Rectangle{ *playerObject }.center());
				if (temp < dist) {
					obj = (*iter);
					dist = temp;
				}
			}
			
			//set states for all halted objects
			auto iterAdvanced = iter1;
			for (auto iterCollide = collideList.begin(); iterCollide != collideList.end() && iterAdvanced != advancedList.end(); ++iterAdvanced) {
				if (iterAdvanced->first == *iterCollide) {
					if (iterAdvanced->first != obj) {
						iterAdvanced->second = false;
					}
					++iterCollide;
				}
			}
		}

	}

	std::for_each(advancedList.begin(), advancedList.end(), [](auto pair) {
		if (pair.second)
			pair.first->advance();
	});



	for (auto& enemy : enemyObjects) {
		if (ticks >= 20) {
			std::cout << enemy->mapPosition().x << " " << enemy->mapPosition().y << " ";
		}
		//enemy->advance();
		enemy->draw();
	}
	if (ticks >= 20) {
		std::cout << '\n';
	}

	for (auto& bullet : bulletObjects) {
		bullet->advance();
		bullet->draw();
	}
	playerObject->draw();
	cursorObject->draw();

	if (ticks == 20)
		ticks = 0;

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
