#ifndef GAME_H_
#define GAME_H_

#include <string.h>

#include "init.h"
#include "player.h"
#include "level.h"
#include "collide.h"
#include "variables.h"

typedef struct Game{
	int nbPlayers;
	Player *players;
	int gameState;
	Level level;
}Game;

Game newGame();

void update(Game *game);

void play(Game *game);

void createPlayers(Game *game);

void collide(Game *game);

void gameRender(Game *game);

#endif