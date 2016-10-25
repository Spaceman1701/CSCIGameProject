#include "renderer.h"
#include <math.h>
#include "game_math.h"
#include "color.h"
#include <iostream>
#include "map.h"
#include <math.h>

Renderer::Renderer(int width, int height) : framebuffer(width, height) {
	this->width = width;
	this->height = height;
	hfov = .73f * height;
	vfov = .2 * height;
	nearClip = 5.f;
	}

void Renderer::update() {

}

Framebuffer* Renderer::getFramebuffer() {
	return &framebuffer; //this should be fine...
}


void Renderer::drawView(Player& p, Map& map) {
	Sector* playerSec = p.getCurrentSector(); //later
	int* top = new int[width];
	int* bottom = new int[width]; //make instance var... context switches expensive... can do it once then memset
	for (int i = 0; i < width; ++i) {
		top[i] = height;
		bottom[i] = 0;
	}
	DrawList drawList;
	DrawSector playerDS = {playerSec, 0, width};
	drawList.push(playerDS);
	//drawSector(playerDS, p, drawList, top, bottom);

	while (!drawList.empty()) {
		DrawSector ds = drawList.front();
		drawList.pop();
		drawSector(ds, p, drawList, top, bottom);
	}

	delete[] top;
	delete[] bottom;
}

void Renderer::drawSector(DrawSector& ds, Player& p, DrawList& drawList, int top[], int bot[]) {
	Vector2 playerLoc = p.getPosition();
	float playerZ = p.getHeight();
	Sector s = *ds.sector;
	std::vector<Wall*> walls = s.getWalls();
	std::cout << "Sector has: " << walls.size() << std::endl;
	for (Wall* w : walls) {
		Sector* nSector = w->getLinkedSector();
		Vector2 v1 = w->getPoints()[0];
		Vector2 v2 = w->getPoints()[1];
		Vector2 cv1 = calcPlayerSpaceVec(v1, playerLoc, p.getAngle(), p.getCosAngle(), p.getSinAngle());
		Vector2 cv2 = calcPlayerSpaceVec(v2, playerLoc, p.getAngle(), p.getCosAngle(), p.getSinAngle());

		if (cv1.y <= 0.0f && cv2.y <= 0.0f) {
			continue; //wall is completely behind player
		}

		std::cout << "y " << cv1.y << std::endl;
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

		int x1 = width/ 2 + (int)(cv1.x * s1.x); //screen x location
		int x2 = width/ 2 + (int)(cv2.x * s2.x);

		if (x1 >= x2 || x1 > ds.maxX || x2 < ds.minX) { //wall takesup 0 or less pixels
			continue; //go to the next wall
		}

		int cceilz = s.getCeilHeight() - playerZ;
		int cfloorz = s.getFloorHeight() - playerZ;

		int yceil1 = height / 2 + (int)(cceilz * s1.y);
		int yfloor1 = height / 2 + (int)(cfloorz * s1.y);
		
		int yceil2 = height / 2 + (int)(cceilz * s2.y);
		int yfloor2 = height / 2 + (int)(cfloorz * s2.y);

		int nyceilz, nyfloorz, nyceil1, nyfloor1, nyceil2, nyfloor2;
		if (nSector) {
			nyceilz = w->getLinkedSector()->getCeilHeight() - p.getHeight();
			nyfloorz = w->getLinkedSector()->getFloorHeight() - p.getHeight();

			nyceil1 = height / 2 + (int)(nyceilz * s1.y);
			nyfloor1 = height / 2 + (int)(nyfloorz * s1.y);

			nyceil2 = height / 2 + (int)(nyceilz * s2.y);
			nyfloor2 = height / 2 + (int)(nyfloorz * s2.y);
		}

		//draw wall
		int startx = fmaxf(x1, ds.minX);
		int endx = fminf(x2, ds.maxX);

		if (nSector && endx > startx) {
			DrawSector nds = { nSector, startx, endx };
			drawList.push(nds);
		}

		for (int x = startx; x < endx; x++) {
			int yceil = (x - x1) * (yceil2 - yceil1) / (x2 - x1) + yceil1; //clamp against draw lists later
			int yfloor = (x - x1) * (yfloor2 - yfloor1) / (x2 - x1) + yfloor1;
			int z = ((x - x1) * (cv2.y - cv1.y) / (x2 - x1) + cv1.y) / 10.0f;

			drawVLine(x, bot[x], yfloor, s.getFloorColor()); //draw floor;
			drawVLine(x, yceil, top[x], s.getCeilColor());

			Color c = Color(255, 255, 255);

			if (nSector != NULL) { //draw step up and step down
				int nyceil = (x - x1) * (nyceil2 - nyceil1) / (x2 - x1) + nyceil1; //clamp against draw lists later
				int nyfloor = (x - x1) * (nyfloor2 - nyfloor1) / (x2 - x1) + nyfloor1;
				top[x] = fminf(nyceil, yceil);
				bot[x] = fmaxf(nyfloor, yfloor);
				if (nyceil < yceil) {
					drawVLine(x, nyceil + 1, yceil - 1, nSector->getCeilStepColor());
				}
				if (nyfloor > yfloor) {
					drawVLine(x, yfloor + 1, nyfloor - 1, nSector->getFloorStepColor());
				}
			}
			if (x != startx && x != endx && !nSector) { //make a nice outline
				drawVLine(x, yfloor + 1, yceil -1, c); //draw wall
				bot[x] = height;
				top[x] = 0;
			}

		}

	}
}

void Renderer::drawVLine(int x, int bottom, int top, Color& color) {
	if (x < 0 || x > 640) {
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
