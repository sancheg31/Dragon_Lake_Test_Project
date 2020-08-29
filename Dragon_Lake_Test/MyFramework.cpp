#include "MyFramework.h"

MyFramework::MyFramework(Size wsize, Size msize, int enemy, int ammo) : windowSize(wsize), mapSize(msize), enemyCount(enemy), ammoAmount(ammo) { }

void MyFramework::PreInit(int& width, int& height, bool& fullscreen) {
	width = windowSize.width;
	height = windowSize.height;
	fullscreen = false;
}

bool MyFramework::Init() {
	showCursor(false);
	player = new PlayerObject({ 0, 0 }, { 0, 0 });
	auto [pwidth, pheight] = player->spriteSize();
	Point startPoint{ windowSize.width / 2 - pwidth / 2, windowSize.height / 2 - pheight / 2 };
	player->moveTo(startPoint);
	return true;
}

void MyFramework::Close() {
	delete player;
}

bool MyFramework::Tick() {
	drawTestBackground();
	player->draw();
	/*if (auto [x, y] = mouseSprite->size(); x > 0 && y > 0)
		mouseSprite->draw();*/
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	//mouseSprite->move(Point{ x, y });
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {

}

void MyFramework::onKeyPressed(FRKey k) {
	auto [x, y] = player->windowRelativePosition();
	if (k == FRKey::RIGHT)
		player->moveTo({ x + 10, y });
	else if (k == FRKey::LEFT)
		player->moveTo({ x - 10, y });
}

void MyFramework::onKeyReleased(FRKey k) {

}
