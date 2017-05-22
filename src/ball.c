#define _GNU_SOURCE

#include <math.h>

#include "ball.h"

Ball newBall(Point center, Vector speed, Color color, int id){
	Ball b;

	b.id     = id;

	b.center = center;
	b.speed  = speed;
	b.vitesse = 0;
	b.dirY = 1;
	b.radius = 10;
	b.color  = color;

	b.thrown = 0;
	b.lost 	 = 0;

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

void changeBallSpeed(Ball *ball, int type){
	int dir;
	switch(type){
		case SPEED_START:
			if(ball->thrown == 0){
				dir = (ball->id%2 == 0) ? 1 : -1;
				ball->vitesse = 2.0;
				printf("vitesse : %f\n", ball->vitesse);
				ball->dirY = dir;
				ball->thrown  = 1;
			}			
			break;

		case SPEED_UP:
			ball->speed.x *= 3;
			/*ball->speed.y *= 3;*/
			break;

		case SPEED_DOWN:
			ball->speed.x /= 3;
			/*ball->speed.y /= 3;*/
			break;

		default:
			break;
	}
}

void ballRun(Ball *ball, float xBar, float wBar){
	if(ball->center.x - ball->radius <= -WINDOW_WIDTH/2 || ball->center.x + ball->radius > WINDOW_WIDTH/2){
		printf("hello\n");
		ball->speed.x *= -1;
		
	}
	if(ball->center.y + ball->radius <= -WINDOW_HEIGHT/2 || ball->center.y - ball->radius > WINDOW_HEIGHT/2){
		/*ball->speed.y *= -1;*/
		ballLost(ball);
	}

	if(ball->thrown == 0){
		ball->center.x = xBar;
	}

	ball->center.x += ball->speed.x;
	if(ball->speed.x == 0){
		ball->center.y += ball->vitesse * ball->dirY; 
		/*printf("dirY      : %d\n", ball->dirY);*/
	}
	else{
		if(fabs(ball->speed.x) > ball->vitesse){
			ball->speed.x = ball->vitesse - ball->vitesse/10;
		}
		printf("dirY : %d\n", ball->dirY);
		ball->center.y += sqrt(ball->vitesse * ball->vitesse - fabs(ball->speed.x) * fabs(ball->speed.x)) * ball->dirY;
		printf("ball->vitesse = %f - ball->speed.x = %f - vv-xx = %f - sqrt(vv-xx) = %f - ball->center.y = %f\n", ball->vitesse, ball->speed.x, ball->vitesse * ball->vitesse - fabs(ball->speed.x) * fabs(ball->speed.x), sqrt(ball->vitesse * ball->vitesse - fabs(ball->speed.x) * fabs(ball->speed.x)), ball->center.y);

	}
}

void ballRender(Ball *ball, float xBar, float wBar){
	ballRun(ball, xBar, wBar);
	ballDraw(ball);
}

void ballLost(Ball *ball){
	ball->lost = 1;
}