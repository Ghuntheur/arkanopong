#ifndef BRICK_H_
#define BRICK_H_

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "variables.h"
#include "geometry.h"
#include "bonus.h"
#include "color.h"

typedef struct Brick{
	int type; 
	Bonus bonus;
	int broken;

	Point center;
	int width;
	int height;
	Color color;
}Brick;

Brick newBrick(int value, int width, int height, int i, int j);

void drawBrick(Brick *brick);

Color colorizeBrick(int type);

void checkBonus(Brick *brick);

#endif