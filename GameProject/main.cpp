#include "framebuffer.h"
#include "renderer.h"
#include "context.h"
#include "sector.h"
#include "player.h"
#include "map.h"
#include <iostream>
#include "map_loader.h"

int main() {

	Context::getInstance()->init(640, 480, 640, 480);
	Renderer ren(640, 480);

	std::string map_location;
	std::cout << "enter the map's file location: ";
	//std::cin >> map_location;

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
	return 0;
}