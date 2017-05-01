#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <math.h>

/**
 * POINT
 */
typedef struct Point{
	float x;
	float y;
}Point;


Point newPoint(float x, float y);

/**
 * VECTEUR
 */

typedef struct Vector{
	float x;
	float y;
}Vector;

Vector newVector(float x, float y);

#endif