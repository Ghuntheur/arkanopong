#include "bar.h"

Bar newBar(Point center, float width, float height, Color color){
	Bar b;

	b.center = center;
	b.width  = width;
	b.height = height;
	b.color  = color;

	return b;
}

void barDraw(Bar *bar){
	float w = bar->width/2;
	float h = bar->height/2;

	float x = bar->center.x;
	float y = bar->center.y;

	glBegin(GL_QUADS);
	glColor3ub(bar->color.r, bar->color.g, bar->color.b);
		glVertex2f(x-w, y+h);
		glVertex2f(x+w, y+h);
		glVertex2f(x+w, y-h);
		glVertex2f(x-w, y-h);
	glEnd();
}

void barMove(Bar *bar, int key){
	bar->center.x += (key == SDLK_RIGHT) ? 60 : -60;

	if(bar->center.x - bar->width/2 < -WINDOW_WIDTH/2){
		bar->center.x = -WINDOW_WIDTH/2 + bar->width/2;
	}
	if(bar->center.x + bar->width/2 > WINDOW_WIDTH/2){
		bar->center.x = WINDOW_WIDTH/2 - bar->width/2;
	}	
	
}