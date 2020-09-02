#include "ScreenArea.h"

#include "PlayerObject.h"
#include "Rectangle.h"
#include "MapArea.h"

ScreenArea::ScreenArea(Size screenDim) : screenDimensions(screenDim) { }

Point ScreenArea::calculateScreenShift(std::shared_ptr<MapArea> mapArea, PlayerObject* playerObject) const {
	if (currentPlayerPosition != playerObject->mapPosition()) {

		currentPlayerPosition = playerObject->mapPosition();

		Point centerPlayer = centerPoint(playerObject);

		upLeftScreenVertex = centerPlayer - (Point)screenDimensions / 2;
		Point downRightScreenVertex = centerPlayer + (Point)screenDimensions / 2; 

		if (upLeftScreenVertex.x < 0) {
			upLeftScreenVertex.x = 0;
		}if (upLeftScreenVertex.y < 0) {
			upLeftScreenVertex.y = 0;
		}
		
		Size mapDimensions = mapArea->size();

		if (downRightScreenVertex.x > mapDimensions.width) {
			upLeftScreenVertex.x = mapDimensions.width - screenDimensions.width;
		}
		if (downRightScreenVertex.y > mapDimensions.height) {
			upLeftScreenVertex.y = mapDimensions.height - screenDimensions.height;
		}
	}
	
	return upLeftScreenVertex;
}

Point ScreenArea::currentShift() const {
	return upLeftScreenVertex;
}

Size ScreenArea::size() const {
	return screenDimensions;
}

