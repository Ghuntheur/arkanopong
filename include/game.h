#ifndef GAME_H_
#define GAME_H_

#include <string.h>

#include "init.h"
#include "player.h"
#include "level.h"
#include "collide.h"
#include "menu.h"
#include "variables.h"

typedef struct Game{
	int nbPlayers;
	Player *players;
	int gameState;
	char textureFolder[100];
	Level level;
	Menu menu;

	Texture winner;
}Game;

Game newGame();

void update(Game *game);

void play(Game *game);

void createPlayers(Game *game);

void collide(Game *game);

void buttonCollide(Game *game, int x, int y);

void gameRender(Game *game);

void playMenu(Game *game);

void applyAction(Game *game, Button *button);

void checkBallLost(Game *game);

int nearestBar(Game *game, Ball *ball);

int checkEndGame(Game *game);

void winner(Game *game);

void winnerDraw(Game *game);

#endif