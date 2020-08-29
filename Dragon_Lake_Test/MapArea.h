#pragma once

#include "Utility.h"

class MapArea
{
public:
	MapArea(Size msize) : mapSize(msize) { }
	MapArea(const MapArea&) = default;
	MapArea(MapArea&&) = default;
	~MapArea() = default;

	Size size() const {
		return mapSize;
	}

private:
	Size mapSize;
};

