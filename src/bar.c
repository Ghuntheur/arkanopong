#include "bar.h"

Bar newBar(Point center, Color color, int id){
	Bar b;

	b.id     = id;
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
	bar->center.x += bar->speed;

	if(bar->center.x - bar->width/2 < -WINDOW_WIDTH/2){
		bar->center.x = -WINDOW_WIDTH/2 + bar->width/2;
	}
	if(bar->center.x + bar->width/2 > WINDOW_WIDTH/2){
		bar->center.x = WINDOW_WIDTH/2 - bar->width/2;
	}	
}

void changeBarSpeed(Bar *bar, int control, int type){
	switch(type){
		case SPEED_UP:
			switch(control){
				case CONTROL_LEFT:
					bar->speed -= 10;
					break;

				case CONTROL_RIGHT:
					bar->speed += 10;
					break;

				case CONTROL_START:
					break;

				default:
					break;
			}
			break;

		case SPEED_STOP:
			bar->speed = 0;
			break;

		default:
			break;
	}	
}

void changeBarSize(Bar *bar, int type){
	switch(type){
		case BAR_BIGGER:
			bar->width *= 2;
			break;

		case BAR_SMALLER:
			bar->width *= 0.5;
			break;

		default:
			break;
	}
}

void changeBarDistance(Bar *bar, int type){
	int dir = (bar->id%2 == 0) ? 1 : -1;
	switch(type){
		case BAR_CLOSER:
			bar->center.y += 100 * dir;
			break;

		case BAR_FURTHER:
			bar->center.y -= 100 * dir;
			break;
	}
}

void barRender(Bar *bar){
	barRun(bar);
	barDraw(bar);
}