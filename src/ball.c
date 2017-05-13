#define _GNU_SOURCE

#include "ball.h"

Ball newBall(Point center, Vector speed, Color color){
	Ball b;

	b.center = center;
	b.speed  = speed;
	b.radius = 10;
	b.color  = color;

	b.thrown = 0;

	return b;
}

void ballDraw(Ball *ball){
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

void changeBallSpeed(Ball *ball, int id, int type){
	int dir;
	switch(type){
		case SPEED_START:
			dir = (id%2 == 0) ? 2 : -2;
			ball->speed.y = dir;
			ball->thrown  = 1;
			break;

		default:
			break;
	}
}

void ballRun(Ball *ball, float xBar){
	if(ball->center.x - ball->radius <= -WINDOW_WIDTH/2 || ball->center.x + ball->radius > WINDOW_WIDTH/2){
		ball->speed.x *= -1;
	}
	if(ball->center.y - ball->radius <= -WINDOW_HEIGHT/2 || ball->center.y + ball->radius > WINDOW_HEIGHT/2){
		ball->speed.y *= -1;
	}

	if(ball->thrown == 0){
		ball->center.x = xBar;
	}

	ball->center.x += ball->speed.x;
	ball->center.y += ball->speed.y;
}

void ballRender(Ball *ball, float xBar){
	ballRun(ball, xBar);
	ballDraw(ball);
}
