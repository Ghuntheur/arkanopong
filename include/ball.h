#ifndef BALL_H_
#define BALL_H_

#include <math.h>
#include <GL/gl.h>

#include "geometry.h"
#include "color.h"

typedef struct Ball{
	Point center;
	Vector speed;
	float radius;
	Color color;
}Ball;

Ball newBall(Point center, Vector speed, float radius, Color color);

void ballDrawing();

#endif