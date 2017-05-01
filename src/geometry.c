#include "geometry.h"

/**
 * POINTS
 */

Point PointXY(float x, float y){
	Point p;

	p.x = x;
	p.y = y;
	
	return p;
}

/**
 * VECTEURS
 */

Vector VectorXY(float x, float y){
	Vector v;

	v.x = x;
	v.y = y;

	return v;
}