#include "bar.h"

Bar newBar(Point center, Color color){
	Bar b;

	b.center = center;
	b.width  = WINDOW_WIDTH/10;
	b.height = 12;
	b.speed  = 0;
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

void barRun(Bar *bar){
	if(bar->center.x - bar->width/2 < -WINDOW_WIDTH/2){
		bar->center.x = -WINDOW_WIDTH/2 + bar->width/2;
	}
	if(bar->center.x + bar->width/2 > WINDOW_WIDTH/2){
		bar->center.x = WINDOW_WIDTH/2 - bar->width/2;
	}

	bar->center.x += bar->speed;
}

void changeBarSpeed(Bar *bar, int key, int type){
	switch(type){
		case SPEED_UP: 
			bar->speed = (key == SDLK_RIGHT || key == SDLK_z) ? 10 : -10;
			break;

		case SPEED_STOP:
			bar->speed = 0;
			break;

		default:
			break;
	}	
}

void barRender(Bar *bar){
	barRun(bar);
	barDraw(bar);
}