#include "player.h"

Player newPlayer(Ball ball, Bar bar, Control control, int id){
	Player p;
	
	p.ball    = ball;
	p.bar     = bar;
	p.control = control;
	p.id      = id;
	p.life    = 3;

	return p;
}

