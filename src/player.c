#include "player.h"

Player newPlayer(Ball ball, Bar bar, int life){
	Player p;
	
	p.ball = ball;
	p.bar  = bar;
	p.life = 3;

	return p;
}