#include "player.h"

Player newPlayer(Ball ball, Bar bar, Control control, Texture textureLife, int id){
	Player p;
	
	p.ball        = ball;
	p.bar         = bar;
	p.control     = control;
	p.textureLife = textureLife;
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

void changePlayerLife(Player *player, int type){
	switch(type){
		case WIN_LIFE:
			player->life++;
			break;

		case LOOSE_LIFE:
			player->life--;
			break;

		default:
			break;
	}
}

void lifeRender(Player *player, Bar *bar){
	int i;

	float w = bar->width/2;
	float h = bar->height/2;

	float x = bar->center.x;
	float y = bar->center.y;
	
	float size = 24;
	int pos = (player->id%2 == 0) ? -1 : 1;
	float decalage = 5*pos;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, player->textureLife.memory);

	for(i=0; i<player->life; i++){
		float dec = (y > 0) ? 20 : 0;
		glBegin(GL_QUADS);
			glTexCoord2f(0, 1); glVertex2f(x-w+i*size, (WINDOW_HEIGHT/2)*pos-10*pos-dec);
			glTexCoord2f(1, 1); glVertex2f(x-w+size+i*size, (WINDOW_HEIGHT/2)*pos-10*pos-dec);
			glTexCoord2f(1, 0); glVertex2f(x-w+size+i*size, (WINDOW_HEIGHT/2)*pos+size-10*pos-dec);
			glTexCoord2f(0, 0); glVertex2f(x-w+i*size, (WINDOW_HEIGHT/2)*pos+size-10*pos-dec);
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}