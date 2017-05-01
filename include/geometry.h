#ifndef GEOMETRY_H_
#define GEOMETRY_H_


/**
 * POINT
 */
typedef struct Point{
	float x;
	float y;
}Point;


Point PointXY(float x, float y);

/**
 * VECTEUR
 */

typedef struct Vector{
	float x;
	float y;
}Vector;

Vector VectorXY(float x, float y);

#endif