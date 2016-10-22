#pragma once
#include "framebuffer.h"
#include "wall.h"
#include "sector.h"
class Renderer {
private:
	Framebuffer framebuffer;
	int width;
	int height;
	float hfov;
	float vfov;
	float fDist;

	Vector2 calcPlayerSpaceVec(Vector2& vec, Vector2& origin, float angle, float cos, float sin);
	Vector2 getPerspectiveScale(Vector2& vec);
public:
	Renderer(int width, int height);
	void update();
	Framebuffer* getFramebuffer();
	void drawSector(Sector& s);
	void drawVLine(float x, float lower, float upper);
};