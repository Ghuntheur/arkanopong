#include "player.h"

Player newPlayer(Ball ball, Bar bar){
	Player p;
	
	p.ball = ball;
	p.bar  = bar;

	return p;
}