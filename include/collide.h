#ifndef COLLIDE_H_
#define COLLIDE_H_

#include "game.h"

typedef struct Box{
	Point center;
	float width; 
	float height;
}Box;

Box newBoxFromBall(Ball *ball);

Box newBoxFromBrick(Brick *brick);

void barCollide(Player *p, int nbPlayers);

int checkBarCollide(Ball *ball, Bar *bar, float *ratio);

int checkBoxBoxCollide(Box *ball, Box *box);

int checkCornersInCircle(Ball *ball, Box *box);

int checkPointInCircle(int x, int y, Ball *ball);

int checkPointInBox(Point *center, Box *box);

int checkThrown(Vector *AC, Vector *AB, Vector *BC);

void brickCollide(Ball *ball, Level *level);

#endif
