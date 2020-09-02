#include "MapArea.h"

MapArea::MapArea(Size msize) : mapSize(msize) { }

Size MapArea::size() const {
	return mapSize;
}
