#define _GNU_SOURCE

#include <math.h>

#include "ball.h"

Ball newBall(Point center, Vector speed, Texture texture, int id){
	Ball b;


	
	b.id     = id;

	b.center = center;
	b.speed  = speed;
	b.radius = 10;
	b.texture = texture;

	b.thrown = 0;
	b.lost 	 = 0;

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
				dir = (ball->id%2 == 0) ? 1 : -1;
				ball->speed.y = 5*dir;
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

		case SPEED_STOP:
			ball->speed.x = 0;
			ball->speed.y = 0;
			break;

		default:
			break;
	}
}

void ballRun(Ball *ball, float xBar, float wBar){
	/**
	 * Rebond contre les parois gauche /droite
	 */
	if(ball->center.x - ball->radius <= -WINDOW_WIDTH/2 || ball->center.x + ball->radius > WINDOW_WIDTH/2){
		ball->speed.x *= -1;
	}

	/**
	 * Perte d'une balle
	 */
	if(ball->center.y + ball->radius <= -WINDOW_HEIGHT/2 || ball->center.y - ball->radius > WINDOW_HEIGHT/2){
		ball->lost = 1;
	}

	/**
	 * Tant que la balle est pas lancée, elle suit en X la barre
	 */
	if(ball->thrown == 0){
		ball->center.x = xBar;
	}

	/**
	 * Updtae de la position de la ball
	 */
	ball->center.x += ball->speed.x;
	ball->center.y += ball->speed.y;
	/*if(ball->speed.x == 0){
		ball->center.y += ball->vitesse * ball->dirY; 
	
	}
	else{
		ball->center.y += sqrt(fabs((ball->vitesse * ball->vitesse) - (ball->speed.x * ball->speed.x))) * ball->dirY;
	}*/
}

void reloadBall(Ball *ball, float xBar, float yBar){
	int pos = (ball->id%2 == 0) ? -1 : 1;
	ball->center = newPoint(xBar, yBar - 20*pos);
	ball->lost = 0;
	ball->thrown = 0;

	changeBallSpeed(ball, SPEED_STOP);
}

void ballRender(Ball *ball, float xBar, float wBar){
	ballRun(ball, xBar, wBar);
	ballDraw(ball);
}
