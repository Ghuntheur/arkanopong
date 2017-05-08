#ifndef GAME_H_
#define GAME_H_

#include "variables.h"
#include "player.h"	

typedef struct Game{
	int nbPlayers;
	Player *players;
	int gameState;
}Game;

int newGame(Game *game, int nbPlayers);

void gameRender(Game *game);

#endif