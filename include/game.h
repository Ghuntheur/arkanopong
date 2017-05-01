#ifndef GAME_H_
#define GAME_H_

#include "player.h"

typedef struct Game{
	int nbPlayers;
	Player *players;	
}Game;

Game newGame(int nbPlayers);

#endif