#pragma once

struct Size;
struct Point;

class Sprite;

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

