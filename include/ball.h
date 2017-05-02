#ifndef BALL_H_
#define BALL_H_

#include <math.h>
#include <GL/gl.h>

#include "geometry.h"
#include "color.h"

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

typedef struct Ball{
	Point center;
	Vector speed;
	float radius;
	Color color;
}Ball;

Ball newBall(Point center, Vector speed, float radius, Color color);

void ballDraw(Ball *ball);

void ballRun(Ball *ball);

void ballRender(Ball *ball);

#endif