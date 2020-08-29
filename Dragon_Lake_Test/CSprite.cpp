
#include "CSprite.h"

#include <Framework.h>

#include "Utility.h"


CSprite::CSprite(const char* path): sprite(createSprite(path)) { }

void CSprite::draw(Point p) {
	auto [x, y] = p;
	drawSprite(sprite, x, y);
}

Size CSprite::size() const {
	int width, height;
	getSpriteSize(sprite, width, height);
	return Size{ width, height };
}

CSprite::~CSprite() {
	destroySprite(sprite);
	sprite = nullptr;
}
