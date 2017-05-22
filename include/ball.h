#ifndef BALL_H_
#define BALL_H_

#include <stdio.h>
#include <math.h>
#include <GL/gl.h>

#include "geometry.h"
#include "texture.h"

#include "variables.h"

typedef struct Ball{
	int id;

	Point center;
	Vector speed;
	float radius;
	int thrown;

	Texture texture;
}Ball;

Ball newBall(Point center, Vector speed, Texture texture, int id);

void ballDraw(Ball *ball);

void ballRun(Ball *ball, float xBar);

void changeBallSpeed(Ball *ball, int type);

void ballRender(Ball *ball, float xBar);

#endif