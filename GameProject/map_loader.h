#pragma once
#include "map.h"
#include "sector.h"
#include "wall.h"
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include "string_utils.h"
class MapLoader {
	typedef std::string string;
private:
	/*keywords and deliminators used in .map files*/
	const char LINE_DELIM = '\n';
	const char ASSIGN_DELIM = '=';
	const char VALUE_DELIM = ',';
	const char PROPERTY_DELIM = ' ';

	const char* COUNT_KEYWORD = "count";
	const char* WSCALE_KEYWORD = "wscale";
	const char* HSCALE_KEYWORD = "hscale";
	const char* LINE_KEYWORD = "line";
	const char* FCOLOR_KEYWORD = "fcolor";
	const char* CCOLOR_KEYWORD = "ccolor";
	const char* FHEIGHT_KEYWORD = "fheight";
	const char* CHEIGHT_KEYWORD = "cheight";
	const char* SECTOR_BEGIN_KEYWORD = "begin";
	const char* SECTOR_END_KEYWORD = "end";
	const char* PORTAL_KEYWORD = "portal";
	const char* SECTOR_ID_KEYWORD = "id";
	const char* FSTEP_COLOR_KEYWORD = "fstepcolor";
	const char* CSTEP_COLOR_KEYWORD = "cstepcolor";
	const char* POSITION_KEYWORD = "pos";
	const char* COLOR_KEYWORD = "color";
	const char* SECTOR_LIGHT_LEVEL = "light";
	/*-------------------------------------------*/
	struct SectorData {
		Color fcolor;
		Color ccolor;
		float fheight;
		float cheight;
		Color fstepcolor;
		Color cstepcolor;
		Color light_level;
		int id;
	};

	struct LineData {
		Color color;
		Vector2 position[2];
		int portal;
		Sector* sector;
	};

	Map *currentMap;
	void splitString(string& s, char delim, std::vector<string>& result);
	Color parseColor(string& data);
	float parseFloat(string& data);
	void parsePoint(string& data, Vector2& v1, Vector2& v2);
	int parseReference(string& data);
	uint8_t parseUInt(string& data);

	Sector* parseSector(std::vector<string>& line, float hscale);
	LineData parseLine(std::vector<string>& line, Sector* sector, float wscale);
public:
	MapLoader();
	Map* loadMap(const char* file_location);
};