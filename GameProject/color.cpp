#include "color.h"

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) : Color(r, g, b, 255){}

Color::Color() : Color(0, 0, 0, 255) {}