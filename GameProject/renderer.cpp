#include "renderer.h"
#include <math.h>
#include "game_math.h"
#include "color.h"
#include <iostream>
#include <SDL2/SDL.h>

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

void Renderer::drawSector(Sector& s, Player& p) {
	Vector2 playerLoc = p.getPosition();
	float playerZ = p.getHeight();

	std::vector<Wall*> walls = s.getWalls();
	for (Wall* w : walls) {
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

		if (x1 >= x2) { //wall takesup 0 or less pixels
			continue; //go to the next wall
		}

		float cceilz = s.getCeilHeight() - playerZ;
		float cfloorz = s.getFloorHeight() - playerZ;

		int yceil1 = height / 2 + (int)(cceilz * s1.y);
		int yfloor1 = height / 2 + (int)(cfloorz * s1.y);
		
		int yceil2 = height / 2 + (int)(cceilz * s2.y);
		int yfloor2 = height / 2 + (int)(cfloorz * s2.y);

		//draw wall
		int startx = x1;
		int endx = x2;
		for (int x = startx; x < endx; x++) {
			int yceil = (x - x1) * (yceil2 - yceil1) / (x2 - x1) + yceil1; //clamp against draw lists later
			int yfloor = (x - x1) * (yfloor2 - yfloor1) / (x2 - x1) + yfloor1;
			int z = ((x - x1) * (cv2.y - cv1.y) / (x2 - x1) + cv1.y) / 10.0f;

			Color c = Color(255, 255, 255);

			if (x != startx && x != endx) { //make a nice outline
				drawVLine(x, yfloor + 1, yceil -1, c); //draw wall
			}
			drawVLine(x, 0, yfloor, s.getFloorColor()); //draw floor;
			drawVLine(x, yceil, height, s.getCeilColor());
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
