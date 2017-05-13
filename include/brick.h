#ifndef BRICK_H_
#define BRICK_H_

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "variables.h"
#include "geometry.h"
#include "color.h"

typedef struct Brick{
	int type; 
	int bonus;
	int broken;

	Point center;
	float width;
	float height;
	Color color;
}Brick;

Brick newBrick(int value, float width, float height, int i, int j);

void drawBrick(Brick *brick);

Color colorizeBrick(int type);

#endif