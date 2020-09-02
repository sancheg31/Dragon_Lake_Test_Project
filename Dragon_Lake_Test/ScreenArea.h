#pragma once

#include <memory>

#include "Utility.h"

class MapArea;
class PlayerObject;

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

