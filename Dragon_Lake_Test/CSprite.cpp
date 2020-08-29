
#include "CSprite.h"

#include <Framework.h>

#include "Utility.h"

class CSprite::Implementation
{
public:
	Implementation(Sprite* spr) : sprite(spr) { 
		getSpriteSize(sprite, size.width, size.height);
	}

	~Implementation() {
		destroySprite(sprite);
	}

	Sprite* sprite;
	Size size;
};


CSprite::CSprite(const char* path) {
	impl = new Implementation(createSprite(path));
}

void CSprite::draw(Point p) {
	auto [x, y] = p;
	drawSprite(impl->sprite, x, y);
}

Size CSprite::size() const {
	return impl->size;
}

CSprite::~CSprite() {
	delete impl;
}
