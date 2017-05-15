#include "bonus.h"

Bonus newBonus(int value, Point center){
	Bonus b;

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

void changeBonusDirection(Bonus *bonus, int direction){
	bonus->direction = (direction == 0) ? -1 : 1;
}

void droppedBonus(Bonus *bonus){
	bonus->dropped = 1;
	changeBonusSpeed(bonus, SPEED_START);
}

void bonusRender(Bonus *bonus){
	if(bonus->dropped == 1 && bonus->caught != 1){
		bonusRun(bonus);
		bonusDraw(bonus);
	}	
}

