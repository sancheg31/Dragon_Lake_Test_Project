#include "ScreenArea.h"

#include "PlayerObject.h"
#include "Rectangle.h"

#include <iostream>

ScreenArea::ScreenArea(const MapArea& area, Size screenDim) : mapArea(area), screenDimensions(screenDim) { }

Point ScreenArea::calculateScreenShift(const PlayerObject& playerObject) const {
	if (currentPlayerPosition != playerObject.position()) {

		currentPlayerPosition = playerObject.position();

		Rectangle playerRectangle{ playerObject.position(), playerObject.size(), VertexPosition::UP_LEFT };
		Point centerPlayer = playerRectangle.center();

		upLeftScreenVertex = Point{ centerPlayer.x - screenDimensions.width / 2, centerPlayer.y - screenDimensions.height / 2 };

		if (upLeftScreenVertex.x < 0) {
			upLeftScreenVertex.x = 0;
		}if (upLeftScreenVertex.y < 0) {
			upLeftScreenVertex.y = 0;
		}

		Point downRightScreenVertex = Point{ centerPlayer.x + screenDimensions.width / 2, centerPlayer.y + screenDimensions.height / 2 };
		Size mapDimensions = mapArea.size();

		if (downRightScreenVertex.x > mapDimensions.width) {
			upLeftScreenVertex.x = mapDimensions.width - screenDimensions.width;
		}
		if (downRightScreenVertex.y > mapDimensions.height) {
			upLeftScreenVertex.y = mapDimensions.height - screenDimensions.height;
		}

		std::cout << "Left screen vertex: " << upLeftScreenVertex.x << " " << upLeftScreenVertex.y << '\n';
		std::cout << "Player's center: " << centerPlayer.x << " " << centerPlayer.y << '\n';
		std::cout << "Player's position: " << currentPlayerPosition.x << " " << currentPlayerPosition.y << "\n\n";
	}
	
	return upLeftScreenVertex;
}

Point ScreenArea::currentShift() const {
	return upLeftScreenVertex;
}

Size ScreenArea::size() const {
	return screenDimensions;
}

