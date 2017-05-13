#include "player.h"

Player newPlayer(Ball ball, Bar bar, int id){
	Player p;
	
	p.ball = ball;
	p.bar  = bar;
	p.id   = id;
	p.life = 3;

	return p;
}

