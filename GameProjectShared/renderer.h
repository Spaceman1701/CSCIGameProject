#pragma once
#include "framebuffer.h"
#include "wall.h"
class Renderer {
private:
	Framebuffer framebuffer;
	int width;
	int height;
	float hfov;
	float vfov;
	float fDist;

	Vector2 calcPlayerSpaceVec(Vector2& vec, Vector2& origin, float angle, float cos, float sin);
public:
	Renderer(int width, int height);
	void update();
	Framebuffer* getFramebuffer();
	void drawWall(Wall& w);
	void drawVLine(float x, float lower, float upper);
};