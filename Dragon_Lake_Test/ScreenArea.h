#pragma once

#include <memory>

#include "Utility.h"

class MapArea;
class PlayerObject;

/*
Represents screen area. Introduced for possible extensions.
Calculates offset from the map upper left corner.
Every GameObject shares its object.
*/

class ScreenArea
{
public:
	ScreenArea(Size screenDim);

	ScreenArea(const ScreenArea&) = default;
	ScreenArea(ScreenArea&&) = default;
	~ScreenArea() = default;

	Point calculateScreenShift(std::shared_ptr<MapArea> area, PlayerObject* playerObject) const;
	Point currentShift() const;
	Size size() const;

private:
	Size screenDimensions;
	mutable Point upLeftScreenVertex{ 0, 0 };
	mutable Point currentPlayerPosition{ 0, 0 };
	
};

