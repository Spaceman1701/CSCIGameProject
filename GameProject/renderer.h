#pragma once
#include "framebuffer.h"
#include "wall.h"
#include "sector.h"
#include "color.h"
#include "player.h"
class Renderer {
private:
	Framebuffer framebuffer;
	int width;
	int height;
	float hfov;
	float vfov;
	float fDist;
	float nearClip;

	Vector2 calcPlayerSpaceVec(Vector2& vec, Vector2& origin, float angle, float cos, float sin);
	Vector2 getPerspectiveScale(Vector2& vec);
public:
	Renderer(int width, int height);
	void update();
	Framebuffer* getFramebuffer();
	void drawSector(Sector& s, Player& p);
	void drawVLine(int x, int lower, int upper, Color& color);
};