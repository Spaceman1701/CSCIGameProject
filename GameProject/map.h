#pragma once
#include "sector.h"
#include <vector>
class Map {
	typedef std::vector<Sector*> SectorList;
private:
	SectorList sectors;
public:
	void addSector(Sector* s);
	SectorList& getSectors();
	~Map();
};