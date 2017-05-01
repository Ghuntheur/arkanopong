#define _GNU_SOURCE

#include <stdio.h>

#include "ball.h"

Ball newBall(Point center, Vector speed, float radius, Color color){
	Ball b;

	b.center     = center;
	b.speed      = speed;
	b.radius     = radius;
	b.color      = color;

	return b;
}

void ballDrawing(Ball *balle){
	int i;
	int precision = 360;
	
	glBegin(GL_POLYGON);
	glColor3ub(balle->color.r, balle->color.g, balle->color.b);

	for(i=0; i<precision; i++){
		float rad = 2*i*M_PI/precision;
		glVertex2f(balle->center.x + cos(rad) * balle->radius, balle->center.y + sin(rad) * balle->radius);
	}
	glEnd();
}
