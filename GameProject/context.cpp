#include "context.h"
Context::Context(int width, int height) {
	this->win_width = width;
	this->win_height = height;
}

bool Context::init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return false;
	}

	win = SDL_CreateWindow("Game", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		SDL_Quit();
		return false;
	}
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL) {
		SDL_DestroyWindow(win);
		SDL_Quit();
		return false;
	}
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, win_width, win_height);
	if (tex == NULL) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return false;
	}
	return true;
}

void Context::swapBuffers(Framebuffer* fb) {
	SDL_RenderClear(ren);
	SDL_UpdateTexture(tex, NULL, *(fb->getPixels()), sizeof(uint8_t));
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);
}

Context::~Context() {
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}