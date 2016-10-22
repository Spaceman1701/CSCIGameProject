#include "framebuffer.h"
#include "renderer.h"
#include "context.h"
#include "sector.h"

int main() {
	Context context(640, 480, 640, 480);
	context.init();
	Renderer ren(640, 480);
	Sector s(0.01f, 3.0f);
	Wall* w = new Wall(Vector2(2.0f, 1.0f), Vector2(0.5f, 2.0f));
	s.addWall(w);

	while (true) {
		ren.drawSector(s);
		context.swapBuffers(ren.getFramebuffer());
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