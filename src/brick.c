#include "brick.h"

Brick newBrick(int value, int width, int height, int i, int j){
	Brick b;

	b.type    = value/10;
	b.bonus   = value%10;
	b.broken  = 0;
	
	b.width  = WINDOW_WIDTH/width;
	b.height = 50;

	b.center = newPoint(
		-WINDOW_WIDTH/2 + b.width*(i+0.5),
		-WINDOW_HEIGHT/2 + (WINDOW_HEIGHT-height*b.height)/2 + b.height*(j+0.5));

	b.color = colorizeBrick(b.type);

	return b;
}

Color colorizeBrick(int type){
	switch(type){
		case FIRST:
			return newColor(255, 0, 0);
			break;
		
		case SECOND:
			return newColor(0, 255, 0);
			break;

		case THIRD:
			return newColor(0, 0, 255);
			break;

		case FOURTH:
			return newColor(255, 0, 255);
			break;

		default:
			return newColor(255, 255, 255);
			break;
	}
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