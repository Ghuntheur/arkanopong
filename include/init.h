#ifndef INIT_H_
#define INIT_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

unsigned int BIT_PER_PIXEL = 32;
Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape();

void setVideoMode();

int initSDL();

#endif