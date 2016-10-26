#pragma once
#include "map.h"
#include "renderer.h"
#include "map_loader.h"
#include "player.h"
class Renderer;
class Player;
class Game {
private:
	Map* map;
	MapLoader map_loader;
	Renderer ren;
	Player player;
public:
	Game(int width, int height);
	void loadMap(const char* file_location);
	void start();
	Map* getMap();
};