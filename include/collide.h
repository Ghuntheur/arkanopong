#ifndef COLLIDE_H_
#define COLLIDE_H_

#include "variables.h"
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

Box newBoxFromBonus(Bonus *bonus);

void barCollide(Ball *ball, Bar *bar, int bonusType);

int checkBarCollide(Ball *ball, Bar *bar);

int checkBrickCollide(Ball *ball, Brick *brick);

int checkBoxBoxCollide(Box *A, Box *B);

int checkCornersInCircle(Ball *ball, Box *box);

int checkPointInCircle(int x, int y, Ball *ball);

int checkPointInBox(Point *center, Box *box);

int checkThrown(Vector *AC, Vector *AB, Vector *BC);

int checkBrickCollideBySide(Ball *ball, Box *box);

int checkBoxIsOutside(Box *box);

void brickCollide(Ball *ball, Level *level);

void bonusCollide(Player *player, Level *level);

#endif
