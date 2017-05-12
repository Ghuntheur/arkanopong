#include "brick.h"

Brick newBrick(int value, int width, int i, int j){
	Brick b;

	b.type    = value/10;
	b.bonus   = value%10;
	b.broken  = 0;

	b.width  = WINDOW_WIDTH/width;
	b.height = 20;

	b.center = newPoint(1,0);

	b.color = newColor(255, 255, 255); 

	return b;
}

void drawBrick(Brick *brick){
	float w = brick->width/2;
	float h = brick->height/2;

	float x = brick->center.x;
	float y = brick->center.y;

	glBegin(GL_QUADS);
	glColor3ub(brick->color.r, brick->color.g, brick->color.b);
		glVertex2f(x-w, y+h);
		glVertex2f(x+w, y+h);
		glVertex2f(x+w, y-h);
		glVertex2f(x-w, y-h);
	glEnd();
}