#include "renderer.h"
#include <math.h>
#include "game_math.h"

Renderer::Renderer(int width, int height) : framebuffer(width, height) {
	this->width = width;
	this->height = height;
}

void Renderer::update() {

}
Framebuffer* Renderer::getFramebuffer() {
	return &framebuffer; //this should be fine...
}
void Renderer::drawWall(Wall& w) { //probably should draw full sector here... 
	Vector2 playerLoc(0, 0);
	Vector2 rv1 = calcPlayerSpaceVec(w.getPoints()[0], playerLoc, 0, 1.0f, 0.0f);
	Vector2 rv2 = calcPlayerSpaceVec(w.getPoints()[0], playerLoc, 0, 1.0f, 0.0f);

	if (rv1.y <= 0 && rv2.y <= 0) { //behind view
		return;
	} //if partly outside need to compute new walls

	Vector2 scale1(0, 0);
	scale1.x = hfov / rv1.x;
	scale1.y = vfov / rv1.y;
}

void Renderer::drawVLine(float x, float bottom, float top) {
	float lowerY = clampf(bottom, 0, height);
	float upperY = clampf(top, 0, height);

	for (int y = lowerY; y < upperY; y++) {
		framebuffer.drawColorPixel(x, y, 255, 255, 255);
	}
}

Vector2 Renderer::calcPlayerSpaceVec(Vector2& vec, Vector2& origin, float angle, float cos, float sin) {
	Vector2 cVec = vec - origin;
	float xp = cVec.x * sin - cVec.y * cos;
	float yp = cVec.x * cos + cVec.y * sin;
	return Vector2(xp, yp);
}
