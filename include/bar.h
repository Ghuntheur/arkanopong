#ifndef BAR_H_
#define BAR_H_

typedef struct Bar{
	Point center;
	float width;
	float height;
	Color color;
}Bar;

Bar newBar(Point center, float width, float height, Color color);

#endif