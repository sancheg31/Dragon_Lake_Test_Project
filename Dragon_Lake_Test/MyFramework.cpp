
#include "MyFramework.h"

#include <iostream>

#include "Rectangle.h"

#include "CSpriteFactory.h"
#include "CSprite.h"

MyFramework::MyFramework(std::shared_ptr<GameObjectFactory> factory, std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea, int enemy, int ammo) : 
					objectFactory(factory), mapArea(marea), screenArea(sarea), enemyCount(enemy), ammoAmount(ammo)  { 

}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen) {
	auto [width_, height_] = screenArea->size();
	width = width_;
	height = height_;
	fullscreen = false;
}

void MyFramework::setEnemyTrajectory(EnemyObject* enemy) {

	auto trajectory = new LinearTrajectoryGenerator();
	std::cout << "enemy center: " << Rectangle{ *enemy }.center().x << " " << Rectangle{ *enemy }.center().y << "\n";
	trajectory->setSegment(Rectangle{ *enemy }.center(), Rectangle{ *playerObject }.center(), 8);
	enemy->setTrajectory(trajectory);
}

bool MyFramework::Init() {
	CSpriteFactory::loadResources();
	Rectangle screenRect(Point{ 0, 0 }, screenArea->size(), VertexPosition::UP_LEFT);

	playerObject = objectFactory->createPlayerObject();
	cursorObject = objectFactory->createCursorObject();

	auto [cx, cy] = screenRect.center();
	auto [px, py] = playerObject->size();
	Point playerPosition{ cx - px / 2, cy - py / 2 };
	
	std::cout << playerPosition.x << " " << playerPosition.y << '\n';
	
	playerObject->setPosition(playerPosition);
	screenArea->calculateScreenShift(mapArea, *playerObject);

	auto [ewidth, eheight] = CSpriteFactory::spriteSize("enemy");
	enemySpawner = new EnemySpawner(objectFactory, Size{ mapArea->size().width - ewidth, mapArea->size().height - eheight });
	enemySpawner->addProhibitZone(playerObject, 4);
	
	enemyObjects = enemySpawner->generate(playerObject, enemyCount);

	showCursor(false);
	return true;
}

void MyFramework::Close() {
	delete enemySpawner;
	delete cursorObject;

	CSpriteFactory::releaseResources();
	for (auto& bullet : bulletObjects)
		delete bullet;
	for (auto& enemy : enemyObjects)
		delete enemy;
	bulletObjects.clear();
	enemyObjects.clear();
}

void MyFramework::restart() {
	Close();
	Init();
}

bool MyFramework::Tick() {

	drawTestBackground();
	Rectangle playerRect{ *playerObject };
	
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
	
	for (auto& enemy : enemyObjects) {
		Rectangle enemyRect{ *enemy };
		if (playerRect.isCollide(enemyRect)) {
			restart();
			return false;
		}
	}

	playerObject->draw();
	for (auto& enemy : enemyObjects) {
		enemy->advance();
		enemy->draw();
	}

	for (auto& bullet : bulletObjects) {
		bullet->advance();
		bullet->draw();
	}
	cursorObject->draw();

	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	cursorObject->setPosition(Point{ x, y });
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {

	if (!isReleased) {

		auto bullet = objectFactory->createBulletObject();
		
		Point startPoint = Rectangle{ *playerObject }.center();
		auto [cx, cy] = cursorObject->mapPosition();
		auto [cwidth, cheight] = cursorObject->size();
		auto [bwidth, bheight] = bullet->size();
		Point cursorPoint = Point{ cx + cwidth / 2 - bwidth / 2, cy + cheight / 2 - bwidth / 2 };

		cursorPoint = findEndPoint(startPoint, cursorPoint);

		auto trajectory = new LinearTrajectoryGenerator;
		trajectory->setSegment(startPoint, cursorPoint, 8);
		bullet->setTrajectory(trajectory);

		bulletObjects.push_back(bullet);
		if (bulletObjects.size() > ammoAmount) {
			std::cout << "yay\n";
			delete *bulletObjects.begin();
			bulletObjects.erase(bulletObjects.begin());
		}
	
	}
}

Point MyFramework::findEndPoint(Point start, Point end) {
	Point Point = end;
	int incX = Point.x - start.x;
	int incY = Point.y - start.y;
	auto [width, height] = mapArea->size();
	while ((Point.x <= width) && ((Point.y <= height)) && (Point.x >= 0) && ((Point.y >= 0))) {
		Point.x += incX;
		Point.y += incY;
	}
	return Point;
}

void MyFramework::onKeyPressed(FRKey k) {
	switch (k) {
	case FRKey::LEFT:
		playerObject->move(Point{ -10, 0 });
		break;
	case FRKey::RIGHT:
		playerObject->move(Point{ 10, 0 });
		break;
	case FRKey::UP:
		playerObject->move(Point{ 0, -10 });
		break;
	case FRKey::DOWN:
		playerObject->move(Point{ 0, 10 });
		break;
	}
	screenArea->calculateScreenShift(mapArea, *playerObject);

	for (auto& enemy : enemyObjects) {
		auto traj = enemy->removeTrajectory();
		traj->setSegment(enemy->mapPosition(), Rectangle{ *playerObject }.center(), 8);
		enemy->setTrajectory(traj);
	}
}

void MyFramework::onKeyReleased(FRKey k) {

}
