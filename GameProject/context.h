#pragma once
#include <SDL2/SDL.h>
#include "framebuffer.h"
#include "renderer.h"
class Context {
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Texture* tex;
	int win_width;
	int win_height;
public:
	Context(int width, int height);
	bool init();
	void swapBuffers(Framebuffer* fb);
	~Context();
};