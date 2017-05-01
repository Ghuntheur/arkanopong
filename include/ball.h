#ifndef BALL_H_
#define BALL_H_

#include "geometry.h"

typedef struct Ball{
	Point center;
	Vector speed;
	float speedValue;
	float radius;
}Ball;

Ball ballCreate(Point center, Vector speed, float speedValue, float radius);

#endif