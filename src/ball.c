#define _GNU_SOURCE

#include <stdio.h>

#include "ball.h"

Ball newBall(Point center, Vector speed, float speedValue, float radius, Color color){
	Ball b;

	b.center     = center;
	b.speed      = speed;
	b.speedValue = speedValue;
	b.radius     = radius;
	b.color      = color;

	return b;
}

void ballDrawing(Ball *balle){
	int i;
	int precision = 360;

	printf("r = %f  g = %f  b = %f\n", balle->color.r, balle->color.g, balle->color.b);
	
	glBegin(GL_POLYGON);
	glColor3ub(balle->color.r, balle->color.g, balle->color.b);
	for(i=0; i<precision; i++){
		float rad = 2*i*M_PI/precision;
		glVertex2f(cos(rad), sin(rad));
	}
	glEnd();
}
