#include "map.h"

void Map::addSector(Sector* s) {
	sectors.push_back(s);
}
Map::SectorList Map::getSectors() {
	return sectors;
}