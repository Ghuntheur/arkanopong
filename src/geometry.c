#include "geometry.h"

/**
 * POINTS
 */

Point newPoint(float x, float y){
	Point p;

	p.x = x;
	p.y = y;
	
	return p;
}

/**
 * VECTEURS
 */

Vector newVector(float x, float y){
	Vector v;

	v.x = x;
	v.y = y;

	return v;
}