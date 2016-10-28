#include "map_loader.h"
#include <stdlib.h>
#include <iostream>
MapLoader::MapLoader() {
	currentMap = NULL; //even though this is a class field, the value is undefined at start... just C++ 05 things.
}
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
	std::vector<Vector2> vertices;
	string line;
	std::vector<string> line_data;
	Sector* current_sector = NULL;
	float wall_scale = 1; //optional values for the file
	float height_scale = 1;
	unsigned int num_sectors = 0;
	while (getline(map_file, line, LINE_DELIM)) {
		splitString(line, PROPERTY_DELIM, line_data);
		std::cout << "parsing: " << line_data[0] << std::endl;
		string keyword = line_data[0];
		if (keyword == COUNT_KEYWORD) {
			num_sectors = parseReference(line_data[1]);
		}
		if (keyword == HSCALE_KEYWORD) {
			height_scale = parseFloat(line_data[1]);
		}
		if (keyword == WSCALE_KEYWORD) {
			wall_scale = parseFloat(line_data[1]);
		}
		if (keyword == VERTEX_KEYWORD) {
			std::cout << "found vertex" << std::endl;
			vertices.push_back(parseVertex(line_data));
		}
		if (keyword == SECTOR_BEGIN_KEYWORD) {
			if (current_sector != NULL) {
				std::cout << "map file may be corrupted... attempting to contiue" << std::endl;
				currentMap->addSector(current_sector);
				current_sector = NULL;
			}
			current_sector = parseSector(line_data, height_scale);
			std::cout << "read sector: " << current_sector->getSectorNum() << std::endl;
		}
		if (current_sector != NULL) {
			if (keyword == LINE_KEYWORD) {
				walls.push_back(parseLine(line_data, current_sector, wall_scale, vertices));
			}
			if (keyword == SECTOR_END_KEYWORD) {
				std::cout << "adding sector to map: " << current_sector->getSectorNum() << std::endl;
				currentMap->addSector(current_sector);
				current_sector = NULL; //map will handle sector deletion in it's destructor
			}
		}
		line_data.clear();
	}
	if (num_sectors != currentMap->getSectors().size()) {
		std::cout << "map loading error: searched for: " << 
			num_sectors << " found: " << currentMap->getSectors().size() << std::endl;
	}

	std::cout << "constructing walls and linking sectors..." << std::endl;
	std::vector<Sector*> map_sectors = currentMap->getSectors();
	for (LineData ld : walls) { //find all the wall references
		Sector* link_sector = NULL;
		if (ld.portal != -1) {
			link_sector = map_sectors[ld.portal];
			std::cout << "link sector location: " << ld.portal << std::endl;
			std::cout << "link sector: " << link_sector->getSectorNum() << std::endl;
		}
		
		ld.sector->addWall(new Wall(ld.position[0], ld.position[1], ld.color, link_sector));
	}
	std::cout << "finished loading map: " << file_location << std::endl;
	return currentMap;
}

Vector2 MapLoader::parseVertex(std::vector<string>& line) {
	std::vector<string> data;
	for (unsigned int i = 0; i < line.size(); ++i) {
		splitString(line[i], ASSIGN_DELIM, data);
		if (data[0] == VERTEX_POS_KEYWORD) {
			return parsePoint2(data[1]);
		}
		data.clear();
	}
}

MapLoader::LineData MapLoader::parseLine(std::vector<string>& line, Sector* sector, float wscale, std::vector<Vector2>& vertices) {
	LineData ld;
	std::vector<string> property_data;
	for (unsigned int i = 0; i < line.size(); ++i) {
		splitString(line[i], ASSIGN_DELIM, property_data);
		if (property_data[0] == POSITION_KEYWORD) {
			Vector2 v1, v2;
			parsePoint4(property_data[1], v1, v2);
			ld.position[0] = v1 * wscale;
			ld.position[1] = v2 * wscale;
		}
		else if (property_data[0] == WALL_POS_INDEX_KEYWORD) {
			std::vector<string> pos_data;
			splitString(property_data[1], VALUE_DELIM, pos_data);
			ld.position[0] = vertices[parseReference(pos_data[0])];
			ld.position[1] = vertices[parseReference(pos_data[1])];
			std::cout << "parsed vert by index reference: " << ld.position[0].x << ", " << ld.position[1].y << std::endl;
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

Sector* MapLoader::parseSector(std::vector<string>& line, float hscale) {
	SectorData sectorData;
	std::vector<string> property_data;
	for (unsigned int i = 0; i < line.size(); ++i) {
		splitString(line[i], ASSIGN_DELIM, property_data);
		if (property_data[0] == FCOLOR_KEYWORD) {
			sectorData.fcolor = parseColor(property_data[1]); //the section after "="
			
		}
		else if (property_data[0] == CCOLOR_KEYWORD) {
			sectorData.ccolor = parseColor(property_data[1]);
		}
		else if (property_data[0] == FHEIGHT_KEYWORD) {
			sectorData.fheight = parseFloat(property_data[1]) * hscale;
		}
		else if (property_data[0] == CHEIGHT_KEYWORD) {
			sectorData.cheight = parseFloat(property_data[1]) * hscale;
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
		else if (property_data[0] == SECTOR_LIGHT_LEVEL) {
			sectorData.light_level = parseColor(property_data[1]);
		}
		property_data.clear();
	}
	Sector* sector = new Sector(sectorData.fheight, sectorData.cheight,
		sectorData.fcolor, sectorData.ccolor, sectorData.fstepcolor, sectorData.cstepcolor, sectorData.light_level);
	sector->setSectorNum(sectorData.id); //add as constructor param
	std::cout << "loaded sector: " << sector->getSectorNum() << std::endl;
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
	uint8_t r = parseUInt(split_data[0]);
	uint8_t g = parseUInt(split_data[1]);
	uint8_t b = parseUInt(split_data[2]);
	return Color(r, g, b);
}

float MapLoader::parseFloat(string& data) {
	return (float)atof(data.c_str());
}

void MapLoader::parsePoint4(string& data, Vector2& v1, Vector2& v2) {
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

Vector2 MapLoader::parsePoint2(string& data) {
	std::vector<string> split_data;
	splitString(data, VALUE_DELIM, split_data);
	std::cout << "paring point: " << split_data[0] << ", " << split_data[1] << std::endl;
	return Vector2(parseFloat(split_data[0]), parseFloat(split_data[1]));
}

int MapLoader::parseReference(string& data) {
	return atoi(data.c_str());
}

uint8_t MapLoader::parseUInt(string& data) {
	return (uint8_t)atoi(data.c_str());
}