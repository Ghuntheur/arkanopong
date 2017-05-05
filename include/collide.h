#ifndef COLLIDE_H_
#define COLLIDE_H_

#include "game.h"

void collide(Game *game);

void barCollide(Game *g);

int checkBarCollide(Ball *ball, Bar *bar, float *ratio);

void brickCollide();

#endif
