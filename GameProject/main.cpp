#include "framebuffer.h"
#include "renderer.h"
#include "context.h"
#include "sector.h"
#include "player.h"
#include "map.h"
#include <iostream>
#include "map_loader.h"
#include "game.h"

int main() {

	std::string map_location = "gamemap.map";
	std::cout << "enter the map's file location: ";
#if 0
	//std::cin >> map_location;
	Context::getInstance()->init(640, 480, 640, 480);
	Renderer ren(640, 480);


	MapLoader ml;
	Map* map = ml.loadMap("gamemap.map");

	Player p;
	Context* c = Context::getInstance();
	while (!c->getShouldQuit()) {
		p.update(map);
		//std::cout << "PLOC:          " << p.getCurrentSector()->getSectorNum() << std::endl;
		ren.drawView(p);
		c->swapBuffers(ren.getFramebuffer());
		ren.getFramebuffer()->clear();
	}
#endif
	Game g(640, 480);
	g.loadMap(map_location.c_str());
	g.start();
	return 0;
}