#pragma once

#include "Utility.h"

/*
Represents map. Introduced for extensions. 
Every GameObject shares its object.
*/
class MapArea
{
public:
	MapArea(Size msize);
	MapArea(const MapArea&) = default;
	MapArea(MapArea&&) = default;
	~MapArea() = default;

	Size size() const;

private:
	Size mapSize;
};

