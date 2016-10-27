#include <iostream>
#include "game.h"

int main() {

	std::string map_location = "gamemap.map";
	std::cout << "enter the map's file location: ";
	Game g(640, 480);
	g.loadMap(map_location.c_str());
	g.start();
	return 0;
}