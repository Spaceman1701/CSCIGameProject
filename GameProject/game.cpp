#include "game.h"
#include "context.h"
Game::Game(int width, int height) : ren(width, height){
	Context::getInstance()->init(width, height, width, height);
}
void Game::loadMap(const char* file_location) {
	map = map_loader.loadMap(file_location);
	player.setMap(map);
}
void Game::start() {
	while (!Context::getInstance()->getShouldQuit()) {
		player.update();
		ren.drawView(player);
		Context::getInstance()->swapBuffers(ren.getFramebuffer());
		ren.getFramebuffer()->clear();
	}
}

Map* Game::getMap() {
	return map;
}