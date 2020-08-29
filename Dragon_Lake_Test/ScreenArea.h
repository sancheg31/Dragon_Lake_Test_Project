#pragma once

#include <memory>

#include "Utility.h"
#include "MapArea.h"


class PlayerObject;

class ScreenArea
{
public:
	ScreenArea(const MapArea& area, Size screenDim);

	ScreenArea(const ScreenArea&) = default;
	ScreenArea(ScreenArea&&) = default;
	~ScreenArea() = default;

	Point calculateScreenShift(const PlayerObject& playerObject) const;

	Point currentShift() const;

	Size size() const;

private:

	const MapArea& mapArea;
	Size screenDimensions;
	mutable Point upLeftScreenVertex{ 0, 0 };
	mutable Point currentPlayerPosition{ 0, 0 };
	
};

