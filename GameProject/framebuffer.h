#pragma once
#include <inttypes.h>
//inline functions are significantly fasters, drawColorPixel is probably going to be 
class Framebuffer {
private:
	uint32_t* colorBuffer;
	int width;
	int height;

	inline int convertCoords(int x, int y) {
		return x + width*(480- y- 1); //store framebuffer upside down. Makes bottom left corner origin
	}
	inline void convertIndex(int i, int* x, int* y) {
		*x = i % width;
		*y = i / width;
	}
public:
	Framebuffer(int width, int height);
	~Framebuffer();
	/*
	*window is mapped [1, width] instead of the typicall [0, width-1] as this makes some operations more intuitive
	*/
	inline void drawColorPixel(int x, int y, uint32_t color) {
		colorBuffer[convertCoords(x, y)] = color;
	}
	inline void drawColorPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
		uint32_t color = (r << 24) + (g << 16) + (b << 8) + 255;
		drawColorPixel(x, y, color);
	}

	inline uint32_t getColor(int x, int y) {
		return colorBuffer[convertCoords(x-1, y-1)];
	}

	void clear();

	uint32_t* getPixels();

	int getWidth();
	int getHeight();
};