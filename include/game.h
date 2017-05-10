#ifndef GAME_H_
#define GAME_H_


#include "init.h"
#include "player.h"
#include "variables.h"

typedef struct Game{
	int nbPlayers;
	Player *players;
	int gameState;
}Game;

Game newGame();

void update(Game *game);

void play(Game *game);

void createPlayers(Game *game);

void gameRender(Game *game);

#endif