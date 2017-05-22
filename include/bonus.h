#ifndef BONUS_H_
#define BONUS_H_

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "variables.h"
#include "player.h"
#include "geometry.h"
#include "color.h"

typedef struct Bonus{
	int id;
	int type;

	Point center;
	Vector speed;
	int direction;
	int width;
	int height;

	int dropped;
	int caught;

	Texture texture;
}Bonus;

Bonus newBonus(int value, Point center, char *textureFolder);

char *texturizeBonus(int type);

void BonusRun(Bonus *bonus);

void bonusDraw(Bonus *bonus);

void changeBonusSpeed(Bonus *bonus, int type);

void changeBonusDirection(Bonus *bonus, int direction);

void changeBonusId(Bonus *bonus, int id);

void changeBonusState(Bonus *bonus, int state);

void bonusRender(Bonus *bonus, int broken);

void applyBonus(Player *player, int bonus);

void checkDisableBonus(Player *player);

void disableBonus(Player *player);

#endif