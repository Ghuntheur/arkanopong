#include "brick.h"

Brick newBrick(int value, int width, int height, int i, int j){
	Brick b;

	b.life    = value/10;
	
	b.broken  = 0;
	
	b.width  = WINDOW_WIDTH/width;
	b.height = 20;

	b.center = newPoint(
		-WINDOW_WIDTH/2 + b.width*(i+0.5),
		WINDOW_HEIGHT/2 - (WINDOW_HEIGHT-height*b.height)/2 - b.height*(j+0.5)
	);

	b.bonus = newBonus(value%10, b.center);
	b.color = colorizeBrick(b.life);

	return b;
}

Color colorizeBrick(int type){
	switch(type){
		case SIMPLE:
			return newColor(255, 0, 0);
			break;
		
		case DOUBLE:
			return newColor(0, 255, 0);
			break;

		case TRIPLE:
			return newColor(0, 0, 255);
			break;

		case UNBREAKABLE:
			return newColor(255, 255, 255);
			break;

		default:
			return newColor(255, 100, 255);
			break;
	}
}

void drawBrick(Brick *brick){
	float w = brick->width/2;
	float h = brick->height/2;

	float x = brick->center.x;
	float y = brick->center.y;

	glBegin(GL_QUADS);
	glColor3ub(brick->color.r, brick->color.g, brick->color.b);
		glVertex2f(x-w, y+h);
		glVertex2f(x+w, y+h);
		glVertex2f(x+w, y-h);
		glVertex2f(x-w, y-h);
	glEnd();
}

void changeBrickLife(Brick *brick){
	if(brick->life == UNBREAKABLE) return;
	brick->life--;
	if(checkBrickIsAlive(brick->life) == EXIT_FAILURE){
		brick->broken = 1;
	}
}

int checkBrickIsAlive(int life){
	return (life > 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void checkBonus(Brick *brick){
	int i;
	for(i=BONUS_EMPTY+1; i<numberOfBonus; i++){
		if(brick->life == i && brick->bonus.type != 0){
			changeBonusState(&brick->bonus, BONUS_DROPPED);
			return;			
		}
	}
}