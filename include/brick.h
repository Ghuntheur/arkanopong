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
	int width;
	int height;
	Color color;
}Brick;

Brick newBrick(int value, int width, int i, int j);

void drawBrick(Brick *brick);

#endif