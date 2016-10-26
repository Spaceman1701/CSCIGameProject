#include "framebuffer.h"
#include <algorithm>

Framebuffer::Framebuffer(int width, int height) {
	this->width = width;
	this->height = height;
	//colorBuffer = new uint32_t[width * height];
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

}

void Framebuffer::clear() {
	std::fill(colorBuffer, colorBuffer + width*height, 0); //probably somewhat safer then memset
} 