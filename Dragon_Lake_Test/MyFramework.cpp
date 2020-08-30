
#include "MyFramework.h"

#include <iostream>

#include "Rectangle.h"
#include "SegmentPixelEngine.h"


MyFramework::MyFramework(GameObjectFactory* factory, std::shared_ptr<MapArea> marea, ScreenArea sarea, int enemy, int ammo) : 
					objectFactory(factory), mapArea(marea), screenArea(sarea), enemyCount(enemy), ammoAmount(ammo)  { }

void MyFramework::PreInit(int& width, int& height, bool& fullscreen) {
	auto [width_, height_] = screenArea.size();
	width = width_;
	height = height_;
	fullscreen = false;
}

bool MyFramework::Init() {

	engine = new SegmentPixelEngine();

	Rectangle screenRect(Point{ 0, 0 }, screenArea.size(), VertexPosition::UP_LEFT);

	playerObject = objectFactory->createPlayerObject(Point{ 0, 0 });
	screenArea.calculateScreenShift(*playerObject);
	cursorObject = objectFactory->createCursorObject();

	auto [cx, cy] = screenRect.center();
	auto [px, py] = playerObject->size();
	Point playerPosition{ cx - px / 2, cx - py / 2 };
	playerObject->moveTo(playerPosition);

	enemyObjects.push_back(objectFactory->createEnemyObject(Point{ 20, 20 }, playerPosition));
	enemyObjects.push_back(objectFactory->createEnemyObject(Point{ 400, 400 }, playerPosition));
	enemyObjects.push_back(objectFactory->createEnemyObject(Point{ 300, 300 }, playerPosition));
	enemyObjects.push_back(objectFactory->createEnemyObject(Point{ 500, 500 }, playerPosition));

	showCursor(false);
	return true;
}

void MyFramework::Close() {
	delete playerObject;
	delete cursorObject;
	delete objectFactory;
	delete engine;

	enemyObjects.clear();
}

bool MyFramework::Tick() {
	drawTestBackground();
	screenArea.calculateScreenShift(*playerObject);
	Rectangle playerRect{ *playerObject };

	for (auto& enemy : enemyObjects) {
		Rectangle enemyRect{ *enemy };
		if (playerRect.isCollide(enemyRect))
			return true;
	}

	playerObject->draw(screenArea);
	cursorObject->draw(screenArea);

	for (auto& enemy : enemyObjects)
		enemy->draw(screenArea);

	if (bullet) {
		auto point = engine->next();
		std::cout << "Point is: " << point.x << " " << point.y << '\n';
		bullet->moveTo(point);
		bullet->draw(screenArea);
	}

	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	cursorObject->moveTo(Point{ x, y });
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	if (!isReleased) {

		bullet = objectFactory->createBulletObject(Point{ 0, 0 }, Point{ 0, 0 });

		Point startPoint = Rectangle{ *playerObject }.center();
		auto [cx, cy] = cursorObject->position();
		auto [cwidth, cheight] = cursorObject->size();
		auto [bwidth, bheight] = bullet->size();
		Point cursorPoint = Point{ cx + cwidth / 2 - bwidth / 2, cy + cheight / 2 - bwidth / 2 };
		cursorPoint = direct(startPoint, cursorPoint);
		engine->setSegment(Line{ startPoint, cursorPoint }, 8);
		
	}
}
Point MyFramework::direct(Point start, Point end) {
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
		playerObject->moveTo(playerObject->position() - Point{10, 0});
		break;
	case FRKey::RIGHT:
		playerObject->moveTo(playerObject->position() + Point{ 10, 0 });
		break;
	case FRKey::UP:
		playerObject->moveTo(playerObject->position() - Point{ 0, 10 });
		break;
	case FRKey::DOWN:
		playerObject->moveTo(playerObject->position() + Point{ 0, 10 });
		break;
	}
	
}

void MyFramework::onKeyReleased(FRKey k) {

}
