#include "context.h"
#include <iostream>
#include <math.h>

Context* Context::instance = NULL;

bool Context::init(int width, int height, int ren_width, int ren_height) {
	std::cout << "Initing SDL" << std::endl;
	should_quit = false;

	this->win_width = width;
	this->win_height = height;
	this->ren_width = ren_width;
	this->ren_height = ren_height;

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
	while (SDL_PollEvent(&ev)) {
		if (ev.type == SDL_KEYDOWN) {
			keymap[ev.key.keysym.sym] = true;
		}
		if (ev.type == SDL_KEYUP) {
			keymap[ev.key.keysym.sym] = false;
		}
		if (ev.type == SDL_QUIT) {
			should_quit = true;
			return; //just gonna quit, no reason to update display
		}
	}

	SDL_RenderClear(ren);
	SDL_UpdateTexture(tex, NULL, (fb->getPixels()), sizeof(uint32_t)*fb->getWidth());
	SDL_RenderCopy(ren, tex, NULL, NULL);
	SDL_RenderPresent(ren);
	SDL_UpdateWindowSurface(win);
	ticks = SDL_GetTicks();
}

bool Context::getShouldQuit() {
	return should_quit;
}
void Context::quit() {
	should_quit = true;
}

Context::~Context() {
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

bool Context::isKeyDown(SDL_Keycode key) {
	if (keymap.find(key) == keymap.end()) {
		keymap[key] = false;
	}
	return keymap[key];
}

Context* Context::getInstance() {
	if (instance == NULL) {
		instance = new Context();
	}
	return instance;
}