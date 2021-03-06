#include "bonus.h"

Bonus newBonus(int value, Point center, char *textureFolder){
	Bonus b;

	b.id        = -1;
	b.type      = value;
	b.center    = center;
	b.speed     = newVector(0, 0);
	b.direction = 0;
	b.texture   = newTexture(textureFolder, texturizeBonus(b.type));
	b.width     = 16;
	b.height    = 32;
	b.dropped   = 0;
	b.caught    = 0;

	return b;
}

char *texturizeBonus(int type){
	if(type > BONUS_EMPTY+1 && type < INVINCIBLE+1) return "bonus.png";
	else if(type > INVINCIBLE && type < numberOfBonus) return "malus.png";

	return "bonus.png";
}

void bonusRun(Bonus *bonus){
	bonus->center.y += bonus->speed.y;
}

void bonusDraw(Bonus *bonus){
	float w = bonus->width/2;
	float h = bonus->height/2;

	float x = bonus->center.x;
	float y = bonus->center.y;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, bonus->texture.memory);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(x-w, y+h); 
		glTexCoord2f(1, 0); glVertex2f(x+w, y+h); 
		glTexCoord2f(1, 1); glVertex2f(x+w, y-h); 
		glTexCoord2f(0, 1); glVertex2f(x-w, y-h); 
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);	
}

void changeBonusSpeed(Bonus *bonus, int type){
	switch(type){
		case SPEED_START:
			bonus->speed.y = 3*bonus->direction;
			break;

		default:
			break;
	}
}

void changeBonusState(Bonus *bonus, int state){
	int type;
	switch(state){
		case BONUS_DROPPED:
			bonus->dropped = 1;
			type = SPEED_START;
			break;
		case BONUS_CAUGHT:
			bonus->caught = 1;
			type = SPEED_STOP;
			break;
	}
	changeBonusSpeed(bonus, type);
}

void changeBonusId(Bonus *bonus, int id){
	bonus->id = id;
}

void changeBonusDirection(Bonus *bonus, int direction){
	bonus->direction = (direction == 0) ? -1 : 1;
}

void bonusRender(Bonus *bonus, int broken){
	if(broken == 1 && bonus->dropped == 1 && bonus->caught != 1){
		bonusRun(bonus);
		bonusDraw(bonus);
	}	
}

void applyBonus(Player *player, int bonus){
	if(checkPlayerHasActiveBonus(player) == EXIT_SUCCESS) return;
	changePlayerBonusParam(player, bonus, BONUS_CAUGHT);

	switch(bonus){
		case BAR_BIGGER:
			changeBarSize(&player->bar, BAR_BIGGER);
			break;
		case BAR_SMALLER:
			changeBarSize(&player->bar, BAR_SMALLER);
			break;
		case BAR_CLOSER:
			changeBarDistance(&player->bar, BAR_CLOSER);
			break;

		case BALL_SPEED_UP:
			changeBallSpeed(&player->ball, SPEED_UP);
			break;
		case BALL_SPEED_DOWN:
			changeBallSpeed(&player->ball, SPEED_DOWN);
			break;
		case BALL_SIZE_UP:
			changeBallSize(&player->ball, BALL_SIZE_UP);
			break;

		case WIN_LIFE:
			changePlayerLife(player, WIN_LIFE);
			break;
		case LOOSE_LIFE:
			changePlayerLife(player, LOOSE_LIFE);
			break;

		default:
			break;
	}
}

void checkDisableBonus(Player *player){
	if(checkPlayerHasActiveBonus(player) == EXIT_SUCCESS){
		unsigned int currentTime = SDL_GetTicks();
		if(currentTime >= player->bonusEndTime){
			disableBonus(player);			
		}
	}
}

void disableBonus(Player *player){
	switch(player->bonusType){
		case BAR_BIGGER:
			changeBarSize(&player->bar, BAR_SMALLER);
			break;
		case BAR_SMALLER:
			changeBarSize(&player->bar, BAR_BIGGER);
			break;
		case BAR_CLOSER:
			changeBarDistance(&player->bar, BAR_FURTHER);
			break;


		case BALL_SPEED_UP:
			changeBallSpeed(&player->ball, SPEED_DOWN);
			break;
		case BALL_SPEED_DOWN:
			changeBallSpeed(&player->ball, SPEED_UP);
			break;
		case BALL_SIZE_UP:
			changeBallSize(&player->ball, BALL_SIZE_DOWN);
			break;
	}
	changePlayerBonusParam(player, player->bonusType, BONUS_DROPPED);
}