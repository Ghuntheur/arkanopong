#ifndef PLAYER_H_
#define PLAYER_H_

#include "variables.h"
#include "ball.h"
#include "bar.h"
#include "control.h"

typedef struct Player{
	int id;
	int life;
	int bonusActive;
	int bonusType;

	unsigned int bonusStartTime;
	unsigned int bonusEndTime;

	Ball ball;
	Bar bar;
	Control control;	
	
}Player;

Player newPlayer(Ball ball, Bar bar, Control control, int id);

int checkPlayerHasActiveBonus(Player *player);

void changePlayerBonusParam(Player *player, int bonus, int state);

void changePlayerLife(Player *player, int type);

#endif