#include "ScreenArea.h"

#include "PlayerObject.h"
#include "Rectangle.h"

ScreenArea::ScreenArea(Size mapDim, Size screenDim) : mapDimensions(mapDim), screenDimensions(screenDim) { }

Point ScreenArea::calculateScreenShift(const PlayerObject& playerObject) const {
	if (currentPlayerPosition != playerObject.position()) {
		Rectangle playerRectangle{ playerObject.position(), playerObject.size(), VertexPosition::UP_LEFT };
		Point centerPlayer = playerRectangle.center();

		upLeftScreenVertex = Point{ centerPlayer.x - screenDimensions.width / 2, centerPlayer.y - screenDimensions.height / 2 };
		Point downRightScreenVertex = Point{ centerPlayer.x + screenDimensions.width / 2, centerPlayer.y + screenDimensions.height / 2 };

		if (upLeftScreenVertex.x < 0 || upLeftScreenVertex.y < 0)
			upLeftScreenVertex = Point{ 0, 0 };
		else if (downRightScreenVertex.x > mapDimensions.width || downRightScreenVertex.y > mapDimensions.height) {
			upLeftScreenVertex = Point{ mapDimensions.width - screenDimensions.width, mapDimensions.height - screenDimensions.height };
		}
	}
	return upLeftScreenVertex;
}

Size ScreenArea::size() const {
	return screenDimensions;
}
