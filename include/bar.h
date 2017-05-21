#ifndef BAR_H_
#define BAR_H_

#include <math.h>
#include <SDL/SDL.h>
#include <GL/gl.h>

#include "variables.h"
#include "geometry.h"
#include "color.h"

typedef struct Bar{
	int id;

	Point center;
	float width;
	float height;
	float speed;
	Color color;
}Bar;

Bar newBar(Point center, Color color, int id);

void barDraw(Bar *bar);

void barRun(Bar *bar);

void changeBarSpeed(Bar *bar, int key, int type);

void changeBarSize(Bar *bar, int type);

void changeBarDistance(Bar *bar, int type);

void barRender(Bar *bar);

#endif