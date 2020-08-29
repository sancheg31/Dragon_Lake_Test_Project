#include "MyFramework.h"

#include <iostream>

#include "Rectangle.h"
#include "Utility.h"

MyFramework::MyFramework(Size msize, Size wsize, int enemy, int ammo) : mapArea(msize), screenArea(mapArea, wsize), playerObject(mapArea, { 0, 0 }),
	enemyCount(enemy), ammoAmount(ammo) {
	enemyObjects.assign({ new EnemyObject{ mapArea, Point{20, 20} }, new EnemyObject{ mapArea, Point{400, 400} } });
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen) {
	auto [width_, height_] = screenArea.size();
	width = width_;
	height = height_;
	fullscreen = false;
}

bool MyFramework::Init() {
	Rectangle screenRect(Point{ 0, 0 }, screenArea.size(), VertexPosition::UP_LEFT);
	auto [cx, cy] = screenRect.center();
	auto [px, py] = playerObject.size();
	Point playerPosition{ cx - px / 2, cx - py / 2 };
	playerObject.moveTo(playerPosition);

	Point shift = screenArea.calculateScreenShift(playerObject);

	showCursor(false);
	return true;
}

void MyFramework::Close() {
	enemyObjects.clear();
}

bool MyFramework::Tick() {
	drawTestBackground();

	Rectangle playerRect{ playerObject };
	
	for (auto& enemy : enemyObjects) {
		Rectangle enemyRect{ *enemy };
		if (playerRect.isCollide(enemyRect))
			return true;
		enemy->draw(screenArea);
	}
	playerObject.draw(screenArea);
		
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {

}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {

}

void MyFramework::onKeyPressed(FRKey k) {
	switch (k) {
	case FRKey::LEFT:
		playerObject.moveTo(playerObject.position() - Point{10, 0});
		break;
	case FRKey::RIGHT:
		playerObject.moveTo(playerObject.position() + Point{ 10, 0 });
		break;
	case FRKey::UP:
		playerObject.moveTo(playerObject.position() - Point{ 0, 10 });
		break;
	case FRKey::DOWN:
		playerObject.moveTo(playerObject.position() + Point{ 0, 10 });
		break;
	}
}

void MyFramework::onKeyReleased(FRKey k) {

}
