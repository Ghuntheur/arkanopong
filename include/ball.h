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
	float vitesse;
	int dirY;
	float radius;
	int thrown;
	int lost;

	Texture texture;
	
}Ball;

Ball newBall(Point center, Vector speed, Texture texture, int id);

void ballDraw(Ball *ball);

void ballRun(Ball *ball, float xBar, float wBar);

void changeBallSpeed(Ball *ball, int type);

void ballRender(Ball *ball, float xBar, float wBar);

void ballLost(Ball *ball);

#endif