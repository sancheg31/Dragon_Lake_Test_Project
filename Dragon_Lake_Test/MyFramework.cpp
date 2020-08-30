
#include "MyFramework.h"

#include <iostream>

#include "Rectangle.h"


MyFramework::MyFramework(GameObjectFactory* factory, std::shared_ptr<MapArea> marea, ScreenArea sarea, int enemy, int ammo) : 
					objectFactory(factory), mapArea(marea), screenArea(sarea), enemyCount(enemy), ammoAmount(ammo)  { }

void MyFramework::PreInit(int& width, int& height, bool& fullscreen) {
	auto [width_, height_] = screenArea.size();
	width = width_;
	height = height_;
	fullscreen = false;
}

bool MyFramework::Init() {
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

	enemyObjects.clear();
	bulletObjects.clear();
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

	for (auto& bullet : bulletObjects)
		bullet->advance();
	for (auto& enemy : enemyObjects)
		enemy->advance();

	for (auto bulletIter = bulletObjects.begin(); bulletIter != bulletObjects.end(); ) {
		Rectangle bulletRect{ **bulletIter };
		bool isErased = false;
		for (auto enemyIter = enemyObjects.begin(); enemyIter != enemyObjects.end(); ) {
			Rectangle enemyRect{ **enemyIter };
			if (bulletRect.isCollide(enemyRect)) {
				enemyIter = enemyObjects.erase(enemyIter);
				isErased = true;
			}
			else {
				++enemyIter;
			}
		}
		if (isErased) {
			bulletIter = bulletObjects.erase(bulletIter);
		}
		else {
			++bulletIter;
		}
	}

	for (auto& enemy : enemyObjects)
		enemy->draw(screenArea);
	for (auto& bullet : bulletObjects)
		bullet->draw(screenArea);

	cursorObject->draw(screenArea);

	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	cursorObject->moveTo(Point{ x, y });
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	if (!isReleased) {
		Point startPoint = Rectangle{ *playerObject }.center();
		auto [cx, cy] = cursorObject->position();
		auto [bwidth, bheight] = cursorObject->size();
		Point cursorPoint = Point{ cx + bwidth / 2, cy + bheight / 2 };

		bulletObjects.push_back(objectFactory->createBulletObject(startPoint, cursorPoint));
		if (bulletObjects.size() > ammoAmount)
			bulletObjects.erase(bulletObjects.begin());
	}
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
