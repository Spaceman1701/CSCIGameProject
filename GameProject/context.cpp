#include "context.h"
#include <iostream>
#include <math.h>
Context::Context(int width, int height, int ren_width, int ren_height) {
	this->win_width = width;
	this->win_height = height;
	this->ren_width = ren_width;
	this->ren_height = ren_height;
}

bool Context::init() {
	std::cout << "Initing SDL" << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		return false;
	}

	win = SDL_CreateWindow("Game", 100, 100, win_width, win_height, SDL_WINDOW_SHOWN);
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
	tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, ren_width, ren_height);
	if (tex == NULL) {
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return false;
	}
	return true;
}


void Context::swapBuffers(Framebuffer* fb) {
	uint32_t deltaTicks = SDL_GetTicks() - ticks;
	std::cout << "Frame time: " << deltaTicks << std::endl;

	SDL_RenderClear(ren);
	SDL_UpdateTexture(tex, NULL, (fb->getPixels()), sizeof(uint32_t)*fb->getWidth());
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);
	SDL_UpdateWindowSurface(win);
	ticks = SDL_GetTicks();
}

Context::~Context() {
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}