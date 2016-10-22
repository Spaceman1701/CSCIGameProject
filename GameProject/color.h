#pragma once
#include <inttypes.h>
class Color {
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
	
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	Color(uint8_t r, uint8_t g, uint8_t b);
	Color();

	inline uint32_t getColor() {
		return (r << 24) + (g << 16) + (b << 8) + a;
	}

	inline static uint32_t getColorValue(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		return (r << 24) + (g << 16) + (b << 8) + a;
	}
};