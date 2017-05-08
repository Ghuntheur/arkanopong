#ifndef INIT_H_
#define INIT_H_

#include <stdio.h>

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "variables.h"

void reshape();

void setVideoMode();

int initSDL();

#endif