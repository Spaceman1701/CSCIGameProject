#pragma once
#include <SDL2/SDL.h>
#include "framebuffer.h"
#include "renderer.h"
#include <unordered_map>
typedef std::unordered_map<Sint32, bool> Keymap;
class Context;
class Context {
private:
	static Context* instance;
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Texture* tex;
	int win_width;
	int win_height;
	int ren_width;
	int ren_height;
	uint32_t ticks;
	Keymap keymap;
	SDL_Event ev;
	bool should_quit;

	Context() {}
public:
	bool init(int width, int height, int render_width, int render_height);
	void swapBuffers(Framebuffer* fb);
	bool isKeyDown(SDL_Keycode key);
	bool getShouldQuit();
	void quit();
	~Context();
	static Context* getInstance();
};