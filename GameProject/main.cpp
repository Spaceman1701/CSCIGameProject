#include "framebuffer.h"
#include "renderer.h"
#include "context.h"
#include "sector.h"
#include "player.h"
#include "map.h"

int main() {
	Context::getInstance()->init(640, 480, 640, 480);
	Renderer ren(640, 480);

	Sector s(-100, 500, Color(100, 100, 100), Color(100, 100, 100), Color(0, 0, 0), Color(0,0,0));
	Sector s2(-50, 200, Color(255, 0, 0), Color(0, 255, 0), Color(255, 0, 0), Color(0, 255, 0));


	Vector2 offset(0, 200);


	Vector2 sv1(-100, -100);
	
	Vector2 sv2(-100, 100);
	Vector2 sp0(-50, 100);
	Vector2 sp1(50, 100);
	Vector2 sv3(100, 100);

	Vector2 sv4(100, -100);




	Wall* si1 = new Wall(sv1 * 5, sv2 * 5);

	Wall* si2p0 = new Wall(sv2 * 5, sp0 * 5);
	Wall* portal = new Wall(sp0 * 5, sp1 * 5, &s2);
	Wall* si2p1 = new Wall(sp1 * 5, sv3 * 5);

	Wall* si3 = new Wall(sv3 * 5, sv4 * 5);
	Wall* si4 = new Wall(sv4 * 5, sv1 * 5);

	s.addWall(si1);
	s.addWall(si2p0);
	s.addWall(portal);
	s.addWall(si2p1);
	s.addWall(si3);
	s.addWall(si4);

	Vector2 s2v1(-100, 100);
	Vector2 s2v2(-100, 200);
	Vector2 s2v3(100, 200);
	Vector2 s2v4(100, 100);

	Wall* s2s1 = new Wall(s2v1 * 5, s2v2 * 5);
	Wall* s2s2 = new Wall(s2v2 * 5, s2v3 * 5);
	Wall* s2s3 = new Wall(s2v3 * 5, s2v4 * 5);
	Wall* s2s4 = new Wall(s2v4 * 5, s2v1 * 5);

	s2.addWall(s2s1);
	s2.addWall(s2s2);
	s2.addWall(s2s3);
	s2.addWall(s2s4);

	Map map;
	map.addSector(&s);
	map.addSector(&s2);

	Player p;
	Context* c = Context::getInstance();
	while (!c->getShouldQuit()) {
		p.update();
		ren.drawView(p, map);
		c->swapBuffers(ren.getFramebuffer());
		ren.getFramebuffer()->clear();
	}
	return 0;
}