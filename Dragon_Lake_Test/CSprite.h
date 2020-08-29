#pragma once

#include "Utility.h"


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
	class Implementation;
	Implementation* impl;
};

