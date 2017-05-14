#ifndef CONTROL_H_
#define CONTROL_H_

#include <SDL/SDL.h>

typedef struct Control{
	int left;
	int right;
	int start;
}Control;

Control newControl(int left, int right, int start);

Control createControl(int i);

#endif