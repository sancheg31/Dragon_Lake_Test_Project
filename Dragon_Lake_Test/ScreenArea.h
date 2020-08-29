#pragma once

#include <memory>

#include "Utility.h"


class PlayerObject;

class ScreenArea
{
public:
	ScreenArea(Size mapDim, Size screenDim);

	ScreenArea(const ScreenArea&) = default;
	ScreenArea(ScreenArea&&) = default;
	~ScreenArea() = default;

	Point calculateScreenShift(const PlayerObject& playerObject) const;

	Size size() const;

private:

	mutable Point upLeftScreenVertex;
	mutable Point currentPlayerPosition;
	Size mapDimensions;
	Size screenDimensions;
};

