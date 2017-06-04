#ifndef PLAYER_H_
#define PLAYER_H_

#include "variables.h"
#include "ball.h"
#include "bar.h"
#include "control.h"

typedef struct Player{
	int id;
	int life;
	int totalLife;
	int bonusActive;
	int bonusType;

	unsigned int bonusStartTime;
	unsigned int bonusEndTime;

	Ball ball;
	Bar bar;
	Control control;
	Texture textureLife;
	
}Player;

Player newPlayer(Ball ball, Bar bar, Control control, Texture textureLife, int id);

int checkPlayerHasActiveBonus(Player *player);

void changePlayerBonusParam(Player *player, int bonus, int state);

void changePlayerLife(Player *player, int type);

void changePlayerTotalLife(Player *player, int type);

void lifeRender(Player *player, Bar *bar);

Point placePlayer(int nbPlayers, int i);

int isAlive(Player *player);

int checkOwnBallLost(int playerId, float yBall);



#endif