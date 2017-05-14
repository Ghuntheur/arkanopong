#ifndef BONUS_H_
#define BONUS_H_

#include "geometry.h"
#include "color.h"

typedef struct Bonus{
	int type;

	Point center;
	int width;
	int height;

	int dropped;
	int caught;

	Color color;
}Bonus;

Bonus newBonus(int value, Point center);

#endif