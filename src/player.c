#include "player.h"

Player newPlayer(Ball ball, Bar bar, Control control, int id){
	Player p;
	
	p.ball        = ball;
	p.bar         = bar;
	p.control     = control;
	p.id          = id;
	p.life        = 3;
	p.bonusActive = 0;
	p.bonusType   = 0;

	p.bonusStartTime = 0;
	p.bonusEndTime   = 0; 

	return p;
}

int checkPlayerHasActiveBonus(Player *player){
	return (player->bonusActive == 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}

void changePlayerBonusParam(Player *player, int bonus, int state){
	switch(state){
		case BONUS_CAUGHT:
			player->bonusActive    = 1;
			player->bonusType      = bonus;
			player->bonusStartTime = SDL_GetTicks();
			player->bonusEndTime   = player->bonusStartTime + BONUS_DURATION;
			break;

		case BONUS_DROPPED:
			player->bonusActive    = 0;
			player->bonusType      = 0;
			player->bonusStartTime = 0;
			break;

		default:
			break;
	}	
}