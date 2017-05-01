#define _GNU_SOURCE

#include "ball.h"

Ball ballCreate(Point center, Vector speed, float speedValue, float radius){
	Ball b;

	b.center     = center;
	b.speed      = speed;
	b.speedValue = speedValue;
	b.radius     = radius;

	return b;
}

void ballDrawing(){
	int i;
	int precision = 360;
	
	glBegin(GL_POLYGON);
	 glColor3ub(255, 0, 0);
	for(i=0; i<precision; i++){
		float rad = 2*i*M_PI/precision;
		glVertex2f(cos(rad), sin(rad));
	}
	glEnd();
}
