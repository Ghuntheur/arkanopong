#ifndef GAME_H_
#define GAME_H_

#include "player.h"

typedef struct Game{
	int nbPlayers;
	Player *players;	
}Game;

int newGame(Game *game, int nbPlayers);

void gameRender(Game *game);

#endif