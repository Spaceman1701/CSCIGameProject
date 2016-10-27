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

	inline Color operator*(const Color left) {
		float f_val = 1.0f / 255.0f;
		float r_float = f_val * (float)r;
		float g_float = f_val * (float)g;
		float b_float = f_val * (float)b;
		float lr_float = left.r * (float)f_val;
		float lg_float = left.g * (float)f_val;
		float lb_float = left.b * (float)f_val;
		
		return Color((uint8_t)(r_float * lr_float * 255), (uint8_t)(g_float * lg_float * 255), 
			(uint8_t)(b_float * lb_float * 255));
	}
};