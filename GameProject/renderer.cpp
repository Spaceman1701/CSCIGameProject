#include "renderer.h"
#include <math.h>
#include "game_math.h"
#include "color.h"
#include <iostream>
#include "map.h"
#include <math.h>
#include <string.h>

Renderer::Renderer(int width, int height) : framebuffer(width, height) {
	this->width = width;
	this->height = height;
	half_width = width / 2;
	half_height = height / 2;

	vfov = 45.0f * DEGTORAD *(float)height;
	hfov = (float)width * vfov / height;
 	nearClip = 9.0f;

	bot = new int[width];
	top = new int[width];
}

void Renderer::update() {

}

Framebuffer* Renderer::getFramebuffer() {
	return &framebuffer; //this should be fine...
}

void Renderer::drawView(Player& p) {
	Sector* playerSec = p.getCurrentSector(); //later
	
	for (int i = 0; i < width; ++i) {
		top[i] = height;
		bot[i] = 0;
	}
	DrawList draw_list;
	DrawSector playerDS = {playerSec, 0, width};
	draw_list.push(playerDS);

	while (!draw_list.empty()) { //draw all the sectors. Later: draw until all columns are filled
		DrawSector ds = draw_list.front();
		draw_list.pop();
		drawSector(ds, p, draw_list, top, bot);
	}
}

void Renderer::drawSector(DrawSector& ds, Player& p, DrawList& draw_list, int top[], int bot[]) {
	Vector2 playerLoc = p.getPosition();
	float playerZ = p.getHeight();
	Sector* s = ds.sector;
	std::vector<Wall*> walls = s->getWalls();
	Color light_level = s->getLightLevel();
	for (Wall* w : walls) {
		Sector* nSector = w->getLinkedSector();
		Vector2 v1 = w->getPoints()[0];
		Vector2 v2 = w->getPoints()[1];
		Vector2 cv1 = calcPlayerSpaceVec(v1, playerLoc, p.getAngle(), p.getCosAngle(), p.getSinAngle());
		Vector2 cv2 = calcPlayerSpaceVec(v2, playerLoc, p.getAngle(), p.getCosAngle(), p.getSinAngle());

		if (cv1.y <= 0.0f && cv2.y <= 0.0f) {
			continue; //wall is completely behind player
		}

		if (cv1.y <= 0.0f) {
			cv1.x = lerp2(cv2.y, cv1.y, cv2.x, cv1.x, nearClip);
			cv1.y = nearClip;
		}
		if (cv2.y <= 0.0f) {
			cv2.x = lerp2(cv1.y, cv2.y, cv1.x, cv2.x, nearClip); 
			cv2.y = nearClip;
		}
		Vector2 s1 = getPerspectiveScale(cv1); //scale vector 1
		Vector2 s2 = getPerspectiveScale(cv2); //scale vector 2

		int x1 = project(half_width, cv1.x, s1.x); //project along each axis independantly for performance reasons
		int x2 = project(half_width, cv2.x, s2.x);

		if (x1 >= x2 || x1 > ds.maxX || x2 < ds.minX) { //wall takesup 0 or less pixels
			continue; //go to the next wall
		}

		float cceilz = s->getCeilHeight() - playerZ;
		float cfloorz = s->getFloorHeight() - playerZ;

		int yceil1 = project(half_height, cceilz, s1.y);
		int yfloor1 = project(half_height, cfloorz, s1.y);
		
		int yceil2 = project(half_height, cceilz, s2.y);
		int yfloor2 = project(half_height, cfloorz, s2.y);

		float nyceilz, nyfloorz;
		int nyceil1, nyfloor1, nyceil2, nyfloor2;
		if (nSector) {
			nyceilz = w->getLinkedSector()->getCeilHeight() - playerZ;
			nyfloorz = w->getLinkedSector()->getFloorHeight() - playerZ;

			nyceil1 = project(half_height, nyceilz, s1.y);
			nyfloor1 = project(half_height, nyfloorz, s1.y);

			nyceil2 = project(half_height, nyceilz, s2.y);
			nyfloor2 = project(half_height, nyfloorz, s2.y);
		}

		//draw wall
		int startx = std::max(x1, ds.minX);
		int endx = std::min(x2, ds.maxX);

		if (nSector && endx > startx) {
			DrawSector nds = { nSector, startx, endx };
			draw_list.push(nds);
		}

		for (int x = startx; x < endx; x++) {
			int yceil = lerp2i(x1, x2, yceil1, yceil2, x);
			int yfloor = lerp2i(x1, x2, yfloor1, yfloor2, x);

			yceil = clampi(yceil, bot[x], top[x]);
			yfloor = clampi(yfloor, bot[x], top[x]);

			//int z = lerp2(x1, x2, cv1.y, cv2.y, x);
			Color floor_color = s->getFloorColor() * light_level;
			drawVLine(x, bot[x], yfloor, floor_color); //draw floor;

			Color ceil_color = s->getCeilColor() * light_level;
			drawVLine(x, yceil, top[x], ceil_color); //draw ceil

			if (nSector != NULL) { //draw step up and step down
				int nyceil = lerp2i(x1, x2, nyceil1, nyceil2, x);
				int nyfloor = lerp2i(x1, x2, nyfloor1, nyfloor2, x);

				top[x] = std::min(nyceil, yceil);
				bot[x] = std::max(nyfloor, yfloor);
				if (nyceil < yceil) {
					Color ceil_step_color = nSector->getCeilStepColor() * light_level;
					drawVLine(x, nyceil + 1, yceil - 1, ceil_step_color);
				}
				if (nyfloor > yfloor) {
					Color floor_step_color = light_level * nSector->getFloorStepColor();
					drawVLine(x, yfloor + 1, nyfloor - 1, floor_step_color);
				}
			}
			if (x != startx && x != endx && !nSector) { //make a nice outline
				Color wall_color = w->getColor() * light_level;
				drawVLine(x, yfloor + 1, yceil -1, wall_color); //draw wall
				bot[x] = height;
				top[x] = 0;
			}

		}

	}
}

void Renderer::drawVLine(int x, int bottom, int top, Color& color) {
	if (x < 0 || x > 640 || bottom > top) {
		return;
	}
	int lowerY = clampi(bottom, 0, height);
	int upperY = clampi(top, 0, height);

	for (int y = lowerY; y < upperY; y++) {
		framebuffer.drawColorPixel(x, y, color.getColor());
	}
}

Vector2 Renderer::calcPlayerSpaceVec(Vector2& vec, Vector2& origin, float angle, float cos, float sin) {
	Vector2 cVec = vec- origin;
	float xp = (cVec.x * cos) - (cVec.y * sin);
	float yp = (cVec.x * sin) + (cVec.y * cos);
	return Vector2(xp, yp);
}

Vector2 Renderer::getPerspectiveScale(Vector2& vec) {
	float xscale = hfov / vec.y;
	float yscale = vfov / vec.y;
	return Vector2(xscale, yscale);
}

int Renderer::project(int center, float value, float scale) {
	return center + (int)(value * scale);
}
