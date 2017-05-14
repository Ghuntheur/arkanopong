#ifndef COLLIDE_H_
#define COLLIDE_H_

#include "game.h"
#include "bonus.h"

typedef struct Box{
	Point center;
	float width; 
	float height;
}Box;

Box newBoxFromBall(Ball *ball);

Box newBoxFromBrick(Brick *brick);

Box newBoxFromBar(Bar *bar);

void barCollide(Ball *ball, Bar *bar);

int checkBarCollide(Ball *ball, Bar *bar, float *ratio);

int checkBrickCollide(Ball *ball, Brick *brick);

int checkBoxBoxCollide(Box *ball, Box *box);

int checkCornersInCircle(Ball *ball, Box *box);

int checkPointInCircle(int x, int y, Ball *ball);

int checkPointInBox(Point *center, Box *box);

int checkThrown(Vector *AC, Vector *AB, Vector *BC);

int checkBrickCollideBySide(Ball *ball, Box *box);

void brickCollide(Ball *ball, Level *level);

#endif
