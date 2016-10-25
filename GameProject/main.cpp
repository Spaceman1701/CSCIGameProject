#include "framebuffer.h"
#include "renderer.h"
#include "context.h"
#include "sector.h"
#include "player.h"

int main() {
	Context::getInstance()->init(640, 480, 640, 480);
	Renderer ren(640, 480);
	Sector s(-100, 500, Color(100, 100, 100), Color(100, 100, 100));
	Vector2 v1(-100, -100);
	
	Vector2 v2(-100, 100);
	Vector2 p0(-50, 100);
	Vector2 p1(50, 100);
	Vector2 v3(100, 100);

	Vector2 v4(100, -100);

	Wall* s1 = new Wall(v1 * 5, v2 * 5);
	Wall* s2 = new Wall(v2* 5, v3 * 5);
	Wall* s3 = new Wall(v3 * 5, v4 * 5);
	Wall* s4 = new Wall(v4 * 5, v1 * 5);

	s.addWall(s1);
	s.addWall(s2);
	s.addWall(s3);
	s.addWall(s4);

	Player p;
	Context* c = Context::getInstance();
	while (!c->getShouldQuit()) {
		p.update();
		ren.drawSector(s, p);
		c->swapBuffers(ren.getFramebuffer());
		ren.getFramebuffer()->clear();
	}
	return 0;
}

#if 0
int main() {
	std::cout << "HHHHHHHHHEEELLLLOOOO LINUX" << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return -1;
	}

	SDL_Window* win = SDL_CreateWindow("Game", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		SDL_Quit();
		return -1;
	}
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) {
		SDL_DestroyWindow(win);
		SDL_Quit();
		return -1;
	}

	bool quit = false;
	SDL_Event e;
	int offset = 0;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
			}
		}
		SDL_Rect rect = SDL_Rect();
		rect.x = offset;
		rect.y = 100;
		rect.h = 100;
		rect.w = 100;
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderDrawRect(ren, &rect);
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderPresent(ren);
		SDL_RenderClear(ren);
		offset++;
		if (offset > 640) {
			offset = 0;
		}
	}

	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
	return 0;
}
#endif