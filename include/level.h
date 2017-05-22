#ifndef LEVEL_H_
#define LEVEL_H_

#include <stdio.h>
#include <stdlib.h>

#include "brick.h"

typedef struct Level{
	char name[100];
	int width;
	int height;
	Brick *bricks;
}Level;

int buildLevel(Level *level, char *textureFolder);

FILE *initLevel(Level *level);

int allocBricksMemory(Level *level);

int createBricks(Level *level, FILE *file, char *textureFolder);

void levelRender(Level *level);

#endif