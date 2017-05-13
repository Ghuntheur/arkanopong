#ifndef PLAYER_H_
#define PLAYER_H_

#include "ball.h"
#include "bar.h"
#include "control.h"

typedef struct Player{
	Ball ball;
	Bar bar;
	Control control;
	
	int id;
	int life;
}Player;

Player newPlayer(Ball ball, Bar bar, Control control, int id);

#endif