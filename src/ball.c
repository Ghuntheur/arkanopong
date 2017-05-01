#include "ball.h"

Ball ballCreate(Point center, Vector speed, float speedValue, float radius){
	Ball b;

	b.center     = center;
	b.speed      = speed;
	b.speedValue = speedValue;
	b.radius     = radius;

	return b;
}
