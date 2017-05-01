#ifndef BAR_H_
#define BAR_H_

#include <math.h>
#include <GL/gl.h>

#include "geometry.h"
#include "color.h"

typedef struct Bar{
	Point center;
	float width;
	float height;
	Color color;
}Bar;

Bar newBar(Point center, float width, float height, Color color);

void barDraw(Bar *bar);

#endif