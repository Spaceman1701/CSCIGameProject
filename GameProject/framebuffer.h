#pragma once
#include <inttypes.h>
//inline functions are significantly fasters, drawColorPixel is probably going to be 
class Framebuffer {
private:
	uint32_t* colorBuffer[];
	uint16_t* depthBuffer[];
	int width;
	int height;

	inline int convertCoords(int x, int y) {
		return x + width*y;
	}
	inline void convertIndex(int i, int* x, int* y) {
		*x = i % width;
		*y = i / width;
	}
public:
	Framebuffer(int width, int height);
	
	inline void drawColorPixel(int x, int y, uint32_t color) {
		(*colorBuffer)[convertCoords(x, y)] = color;
	}
	inline void drawColorPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
		uint32_t color = (255 << 24) + (r << 16) + (g << 8) + b;
		drawColorPixel(x, y, color);
	}

	inline uint32_t getColor(int x, int y) {
		return (*colorBuffer)[convertCoords(x, y)];
	}

	uint32_t** getPixels();
};