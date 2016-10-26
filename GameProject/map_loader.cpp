#include "map_loader.h"
#include <stdlib.h>
#include <iostream>

Map* MapLoader::loadMap(const char* file_location) {
	std::cout << "loading file: " << file_location << std::endl;
	if (currentMap != NULL) {
		delete currentMap;
	}
	currentMap = new Map();
	std::ifstream map_file;
	map_file.open(file_location);
	if (map_file.fail()) {
		std::cout << "failed to load file!" << std::endl;
	}
	std::vector<LineData> walls;
	string line;
	std::vector<string> line_data;
	Sector* current_sector = NULL;
	while (getline(map_file, line, LINE_DELIM)) {
		splitString(line, PROPERTY_DELIM, line_data);
		std::cout << "parsing: " << line_data[0] << std::endl;
		if (line_data[0] == SECTOR_BEGIN_KEYWORD) {
			current_sector = parseSector(line_data);
			
		}
		if (current_sector != NULL) {
			if (line_data[0] == LINE_KEYWORD) {
				walls.push_back(parseLine(line_data, current_sector));
			}
			if (line_data[0] == SECTOR_END_KEYWORD) {
				currentMap->addSector(current_sector);
				current_sector = NULL; //map will handle sector deletion in it's destructor
			}
		}
		line_data.clear();
	}
	std::vector<Sector*> map_sectors = currentMap->getSectors();
	for (LineData ld : walls) { //find all the wall references
		Sector* link_sector = NULL;
		if (ld.portal != -1) {
			link_sector = map_sectors[ld.portal];
			std::cout << "link sector: " << link_sector->getSectorNum() << std::endl;
		}
		
		ld.sector->addWall(new Wall(ld.position[0], ld.position[1], link_sector));
	}

	return currentMap;
}

MapLoader::LineData MapLoader::parseLine(std::vector<string>& line, Sector* sector) {
	LineData ld;
	std::vector<string> property_data;
	for (int i = 0; i < line.size(); ++i) {
		splitString(line[i], ASSIGN_DELIM, property_data);
		if (property_data[0] == POSITION_KEYWORD) {
			Vector2 v1, v2;
			parsePoint(property_data[1], v1, v2);
			ld.position[0] = v1;
			ld.position[1] = v2;
		}
		else if (property_data[0] == COLOR_KEYWORD) {
			ld.color = parseColor(property_data[1]);
		}
		else if (property_data[0] == PORTAL_KEYWORD) {
			ld.portal = parseReference(property_data[1]);
		}
		property_data.clear();
	}
	ld.sector = sector;
	return ld;
}

Sector* MapLoader::parseSector(std::vector<string>& line) {
	SectorData sectorData;
	std::vector<string> property_data;
	for (int i = 0; i < line.size(); ++i) {
		splitString(line[i], ASSIGN_DELIM, property_data);
		if (property_data[0] == FCOLOR_KEYWORD) {
			sectorData.fcolor = parseColor(property_data[1]); //the section after "="
			
		}
		else if (property_data[0] == CCOLOR_KEYWORD) {
			sectorData.ccolor = parseColor(property_data[1]);
		}
		else if (property_data[0] == FHEIGHT_KEYWORD) {
			sectorData.fheight = parseFloat(property_data[1]);
		}
		else if (property_data[0] == CHEIGHT_KEYWORD) {
			sectorData.cheight = parseFloat(property_data[1]);
		}
		else if (property_data[0] == FSTEP_COLOR_KEYWORD) {
			sectorData.fstepcolor = parseColor(property_data[1]);
		}
		else if (property_data[0] == CSTEP_COLOR_KEYWORD) {
			sectorData.cstepcolor = parseColor(property_data[1]);
		}
		else if (property_data[0] == SECTOR_ID_KEYWORD) {
			sectorData.id = parseReference(property_data[1]);
		}
		property_data.clear();
	}
	Sector* sector = new Sector(sectorData.fheight, sectorData.cheight,
		sectorData.fcolor, sectorData.ccolor, sectorData.fstepcolor, sectorData.cstepcolor);
	sector->setSectorNum(sectorData.id); //add as constructor param
	return sector;
}

void MapLoader::splitString(string& s, char delim, std::vector<string>& result) {
	std::stringstream ss;
	ss.str(s);
	string seg;
	while (getline(ss, seg, delim)) {
		result.push_back(seg);
	}
}

Color MapLoader::parseColor(string& data) {
	std::vector<string> split_data;
	splitString(data, VALUE_DELIM, split_data);
	float r = parseFloat(split_data[0]);
	float g = parseFloat(split_data[1]);
	float b = parseFloat(split_data[2]);
	return Color(r, g, b);
}

float MapLoader::parseFloat(string& data) {
	return atof(data.c_str());
}

void MapLoader::parsePoint(string& data, Vector2& v1, Vector2& v2) {
	std::vector<string> split_data;
	splitString(data, VALUE_DELIM, split_data);
	float x = parseFloat(split_data[0]);
	float y = parseFloat(split_data[1]);
	float x1 = parseFloat(split_data[2]);
	float y1 = parseFloat(split_data[3]);
	v1.x = x;
	v1.y = y;
	v2.x = x1;
	v2.y = y1;
}

int MapLoader::parseReference(string& data) {
	return atoi(data.c_str());
}