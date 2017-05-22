#define _GNU_SOURCE

#include "ball.h"

Ball newBall(Point center, Vector speed, Texture texture, int id){
	Ball b;

	b.id      = id;
	
	b.center  = center;
	b.speed   = speed;
	b.radius  = 10;
	b.texture = texture;
	
	b.thrown  = 0;

	return b;
}

void ballDraw(Ball *ball){
	int i;
	int precision = 360;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ball->texture.memory);

	glBegin(GL_POLYGON);

	for(i=0; i<precision; i++){
		float rad = 2*i*M_PI/precision;
		glTexCoord2f(cos(rad), sin(rad));
		glVertex2f(ball->center.x + cos(rad) * ball->radius, ball->center.y + sin(rad) * ball->radius);
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);	
}

void changeBallSpeed(Ball *ball, int type){
	int dir;
	switch(type){
		case SPEED_START:
			if(ball->thrown == 0){
				dir = (ball->id%2 == 0) ? 2 : -2;
				ball->speed.y = dir;
				ball->thrown  = 1;
			}			
			break;

		case SPEED_UP:
			ball->speed.x *= 3;
			ball->speed.y *= 3;
			break;

		case SPEED_DOWN:
			ball->speed.x /= 3;
			ball->speed.y /= 3;
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
