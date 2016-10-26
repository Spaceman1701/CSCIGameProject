#include "map.h"

void Map::addSector(Sector* s) {
	sectors.push_back(s);
}
Map::SectorList& Map::getSectors() {
	return sectors;
}

Map::~Map() {
	for (Sector* s : sectors) {
		delete s;
	}
}