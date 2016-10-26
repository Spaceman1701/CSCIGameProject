#pragma once
#include "framebuffer.h"
#include "wall.h"
#include "sector.h"
#include "color.h"
#include "player.h"
#include "map.h"
#include <queue>
struct DrawSector {
	Sector* sector;
	int minX;
	int maxX;
};
class Renderer {


	typedef std::queue<DrawSector> DrawList;
	typedef std::vector<int> ClipList;
private:
	Framebuffer framebuffer;
	int width;
	int height;
	
	float hfov;
	float vfov;
	float fDist;
	float nearClip;

	int avar;

	ClipList top;
	ClipList bot;
	

	Vector2 calcPlayerSpaceVec(Vector2& vec, Vector2& origin, float angle, float cos, float sin);
	Vector2 getPerspectiveScale(Vector2& vec);
	void drawSector(DrawSector& s, Player& p, DrawList& drawList, ClipList& top, ClipList& bottom);
	int project(int center, float value, float scale);
public:
	Renderer(int width, int height);
	void update();
	Framebuffer* getFramebuffer();
	
	void drawVLine(int x, int lower, int upper, Color& color);
	void drawView(Player& p);
};