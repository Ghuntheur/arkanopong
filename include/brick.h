#ifndef BRICK_H_
#define BRICK_H_

#include <SDL/SDL.h>
#include <GL/gl.h>

#include "variables.h"
#include "geometry.h"
#include "bonus.h"
#include "texture.h"

typedef struct Brick{
	int life;
	Bonus bonus;
	int broken;

	Point center;
	int width;
	int height;
	
	Texture texture;
}Brick;

Brick newBrick(int value, int width, int height, int i, int j, char *textureFolder);

int checkBrickIsAlive(int life);

void drawBrick(Brick *brick);

char *texturizeBrick(int type);

void changeBrickLife(Brick *brick);

void checkBonus(Brick *brick);

#endif