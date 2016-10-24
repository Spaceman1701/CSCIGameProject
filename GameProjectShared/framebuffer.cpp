#include "framebuffer.h"

Framebuffer::Framebuffer(int width, int height) {
	this->width = width;
	this->height = height;
	colorBuffer = new uint32_t[width * height];
	depthBuffer = new uint16_t[width * height];
}

uint32_t* Framebuffer::getPixels() {
	return colorBuffer;
}


int Framebuffer::getWidth() {
	return width;
}
int Framebuffer::getHeight() {
	return height;
}

Framebuffer::~Framebuffer() {
	delete[] colorBuffer;
	delete[] depthBuffer;
}