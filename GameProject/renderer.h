#pragma once
#include "framebuffer.h"
class Renderer {
public:
	void update();
	Framebuffer* getFramebuffer();
};