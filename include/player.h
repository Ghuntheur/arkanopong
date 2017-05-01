#ifndef PLAYER_H_
#define PLAYER_H_

#include "ball.h"
#include "bar.h"

typedef struct Player{
	Ball ball;
	Bar bar;
}Player;

Player newPlayer(Ball ball, Bar bar);

#endif