#include "bar.h"

Bar newBar(Point center, float width, float height, Color color){
	Bar b;

	b.center = center;
	b.width  = width;
	b.height = height;
	b.color  = color;

	return b;
}