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

Vector newVectorFromPoint(Point *A, Point *B){
	Vector v;
	
	v.x = B->x - A->x;
	v.y = B->y - A->y;

	return v;
}

float dotProduct(Vector *A, Vector *B){
	return A->x*B->x + A->y*B->y;
}