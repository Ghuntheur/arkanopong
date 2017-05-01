#define _GNU_SOURCE

#include "ball.h"

Ball newBall(Point center, Vector speed, float radius, Color color){
	Ball b;

	b.center     = center;
	b.speed      = speed;
	b.radius     = radius;
	b.color      = color;

	return b;
}

void ballDrawing(Ball *ball){
	int i;
	int precision = 360;
	
	glBegin(GL_POLYGON);
	glColor3ub(ball->color.r, ball->color.g, ball->color.b);

	for(i=0; i<precision; i++){
		float rad = 2*i*M_PI/precision;
		glVertex2f(ball->center.x + cos(rad) * ball->radius, ball->center.y + sin(rad) * ball->radius);
	}
	glEnd();
}

void ballRun(Ball *ball){
	if(ball->center.x - ball->radius <= -WINDOW_WIDTH || ball->center.x + ball->radius > WINDOW_WIDTH){
		ball->speed.x *= -1;
	}
	if(ball->center.y - ball->radius <= -WINDOW_HEIGHT || ball->center.y + ball->radius > WINDOW_HEIGHT){
		ball->speed.y *= -1;
	}
	ball->center.x += ball->speed.x;
	ball->center.y += ball->speed.y;
}

void ballDisplay(Ball *ball){
	ballRun(ball);
	ballDrawing(ball);
}
