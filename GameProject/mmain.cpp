#include "context.h"
#include "framebuffer.h"

int main() {
	Framebuffer fb(640, 480);
	Context context(640, 480, 640, 480);
	context.init();
	fb.drawColorPixel(320, 240, 255, 255, 0);
	fb.drawColorPixel(640, 480, 255, 0, 0);
	while (true) {
		for (int x = 1; x < 641; x++) {
			for (int y = 1; y < 481; y++) {
				fb.drawColorPixel(x, y, 255, 255, 255);
			}
		}
		context.swapBuffers(&fb);
	}
	return 0;
}