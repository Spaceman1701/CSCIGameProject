#include <iostream>
#include "game.h"

int main() {

	std::string map_location = "gamemap2.map";
	std::cout << "enter the map's file location: ";
	std::cin >> map_location;
	Game g(640, 480);
	g.loadMap(map_location.c_str());
	g.start();
	return 0;
}