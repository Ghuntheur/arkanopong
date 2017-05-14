#ifndef BONUS_H_
#define BONUS_H_

#include "brick.h"

typedef struct Bonus{
	int type;

	Point center;
	int width;
	int height;

	int caught;
}Bonus;

#endif;