#ifndef BONUS_H_
#define BONUS_H_

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "variables.h"
#include "geometry.h"
#include "color.h"

typedef struct Bonus{
	int type;

	Point center;
	Vector speed;
	int direction;
	int width;
	int height;

	int dropped;
	int caught;

	Color color;
}Bonus;

Bonus newBonus(int value, Point center);

void BonusRun(Bonus *bonus);

void bonusDraw(Bonus *bonus);

void changeBonusSpeed(Bonus *bonus, int type);

void changeBonusDirection(Bonus *bonus, int direction);

void droppedBonus(Bonus *bonus);

void bonusRender(Bonus *bonus);

#endif