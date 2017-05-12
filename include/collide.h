#ifndef COLLIDE_H_
#define COLLIDE_H_

#include "game.h"

void collide(Game *game);

void barCollide(Player *p, int nbPlayers);

int checkBarCollide(Ball *ball, Bar *bar, float *ratio);

void brickCollide();

#endif
