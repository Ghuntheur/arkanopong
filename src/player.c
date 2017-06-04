#include "player.h"

Player newPlayer(Ball ball, Bar bar, Control control, Texture textureLife, int id){
	Player p;
	
	p.ball        = ball;
	p.bar         = bar;
	p.control     = control;
	p.textureLife = textureLife;
	p.id          = id;
	p.life        = 1;
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

void changePlayerTotalLife(Player *player, int type){
	switch(type){
		case WIN_LIFE:
			player->totalLife++;
			break;

		case LOOSE_LIFE:
			player->totalLife--;
			break;

		default:
			break;
	}
}

void lifeRender(Player *player, Bar *bar){
	int i;

	float w = bar->width/2;

	float x = bar->center.x;
	float y = bar->center.y;
	
	float size = 24;
	int pos = (player->id%2 == 0) ? -1 : 1;

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

Point placePlayer(int nbPlayers, int i){
	int pos = (i%2 == 0) ? -1 : 1;
	int pos4;
	Point point;
	switch(nbPlayers){
		case 2:
			point = newPoint(0, 360*pos);
			break;
		case 4:
			pos4 = (i<nbPlayers/2) ? 1 : -1;
			point = newPoint(-200*pos4, 360*pos);
			break;
		case 6:
			point = newPoint(-250+250*(i/2), 360*pos);
			break;
		default:
			point = newPoint(0, 0);
			break;
	}
	return point;
}

int isAlive(Player *player){
	return (player->life > 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int checkOwnBallLost(int playerId, float yBall){
	return (playerId%2 == 0 && yBall < 0) ? EXIT_SUCCESS : (playerId%2 == 1 && yBall > 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}