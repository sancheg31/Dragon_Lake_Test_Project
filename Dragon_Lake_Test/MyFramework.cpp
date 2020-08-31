
#include "MyFramework.h"

#include <iostream>

#include "Rectangle.h"

#include "CSpriteFactory.h"

MyFramework::MyFramework(GameObjectFactory* factory, std::shared_ptr<MapArea> marea, std::shared_ptr<ScreenArea> sarea, int enemy, int ammo) : 
					objectFactory(factory), mapArea(marea), screenArea(sarea), enemyCount(enemy), ammoAmount(ammo)  { }

void MyFramework::PreInit(int& width, int& height, bool& fullscreen) {
	auto [width_, height_] = screenArea->size();
	width = width_;
	height = height_;
	fullscreen = false;
}

EnemyObject* MyFramework::generateEnemyObject(Point p) {
	auto enemy = objectFactory->createEnemyObject();
	enemy->setPosition(p);

	auto trajectory = new LinearTrajectoryGenerator();
	trajectory->setSegment(Rectangle{ *enemy }.center(), Rectangle{ *playerObject }.center(), 8);
	enemy->setTrajectory(trajectory);
	return enemy;
}

bool MyFramework::Init() {

	Rectangle screenRect(Point{ 0, 0 }, screenArea->size(), VertexPosition::UP_LEFT);

	playerObject = objectFactory->createPlayerObject();
	screenArea->calculateScreenShift(mapArea, *playerObject);
	cursorObject = objectFactory->createCursorObject();

	auto [cx, cy] = screenRect.center();
	auto [px, py] = playerObject->size();
	Point playerPosition{ cx - px / 2, cx - py / 2 };
	playerObject->setPosition(playerPosition);
	
	enemyObjects.push_back(generateEnemyObject(Point{ 20, 20 }));
	//enemyObjects.push_back(generateEnemyObject(Point{ 100, 100 }));
	enemyObjects.push_back(generateEnemyObject(Point{ 400, 400 }));
	enemyObjects.push_back(generateEnemyObject(Point{ 500, 500}));

	showCursor(false);
	return true;
}

void MyFramework::Close() {
	GameObject::releaseResources();
	bulletObjects.clear();
	enemyObjects.clear();
}

bool MyFramework::Tick() {
	drawTestBackground();
	Rectangle playerRect{ *playerObject };

	for (auto& enemy : enemyObjects) {
		Rectangle enemyRect{ *enemy };
		if (playerRect.isCollide(enemyRect))
			return true;
	}

	playerObject->draw();
	cursorObject->draw();

	for (auto& enemy : enemyObjects) {
		enemy->advance();
		enemy->draw();
	}

	for (auto& bullet : bulletObjects) {
		bullet->advance();
		bullet->draw();
	}
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

		/*std::cout << "Start Point: " << startPoint.x << " " << startPoint.y << '\n';
		std::cout << "Cursor Point: " << cursorPoint.x << " " << cursorPoint.y << '\n';
		*/
		cursorPoint = findEndPoint(startPoint, cursorPoint);

		auto trajectory = new LinearTrajectoryGenerator;
		trajectory->setSegment(startPoint, cursorPoint, 8);
		bullet->setTrajectory(trajectory);

		bulletObjects.push_back(bullet);
		if (bulletObjects.size() > ammoAmount)
			bulletObjects.erase(bulletObjects.begin());
		/*
		std::cout << "Bullet amount: " << bulletObjects.size() << '\n';*/
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
