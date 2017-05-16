#include "bonus.h"

Bonus newBonus(int value, Point center){
	Bonus b;

	b.id        = -1;
	b.type      = value;
	b.center    = center;
	b.speed     = newVector(0, 0);
	b.direction = 0;
	b.color     = newColor(255, 255, 255);
	b.width     = 16;
	b.height    = 32;
	b.dropped   = 0;
	b.caught    = 0;

	return b;
}

void bonusRun(Bonus *bonus){
	bonus->center.y += bonus->speed.y;
}

void bonusDraw(Bonus *bonus){
	float w = bonus->width/2;
	float h = bonus->height/2;

	float x = bonus->center.x;
	float y = bonus->center.y;

	glBegin(GL_QUADS);
	glColor3ub(bonus->color.r, bonus->color.g, bonus->color.b);
		glVertex2f(x-w, y+h);
		glVertex2f(x+w, y+h);
		glVertex2f(x+w, y-h);
		glVertex2f(x-w, y-h);
	glEnd(); 
}

void changeBonusSpeed(Bonus *bonus, int type){
	switch(type){
		case SPEED_START:
			bonus->speed.y = bonus->direction;
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

		default:
			break;
	}
}

void checkDisableBonus(Player *player){
	if(checkPlayerHasActiveBonus(player) == EXIT_SUCCESS){
		unsigned int currentTime = SDL_GetTicks();
		printf("currentTime = %d  endBonus = %d\n", currentTime, player->bonusEndTime );
		if(currentTime >= player->bonusEndTime){
			printf("il faut supp\n");
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
	}
	changePlayerBonusParam(player, player->bonusType, BONUS_DROPPED);
}