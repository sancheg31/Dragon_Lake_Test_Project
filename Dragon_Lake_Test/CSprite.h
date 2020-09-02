#pragma once

struct Size;
struct Point;

class Sprite;

/*
Represents wrapper(actually Adapter, but around C-style code) around Sprite object.
*/
class CSprite
{
public:
	CSprite(const char* path);
	CSprite(const CSprite&) = delete;
	CSprite(CSprite&&) = default;
	~CSprite();

	void draw(Point p);
	Size size() const;

private:
	Sprite* sprite;
};

