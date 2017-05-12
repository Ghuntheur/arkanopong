#ifndef COLLIDE_H_
#define COLLIDE_H_

#include "game.h"

typedef struct Box{
	Point center;
	float width; 
	float height;
}Box;

void collide(Game *game);

Box newBoxFromBall(Ball *ball);

Box newBoxFromBrick(Brick *brick);

void barCollide(Player *p, int nbPlayers);

int checkBarCollide(Ball *ball, Bar *bar, float *ratio);

int checkBoxBoxCollide(Box *ball, Box *box);

void brickCollide(Ball *ball, Level *level);

#endif
