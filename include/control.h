#ifndef CONTROL_H_
#define CONTROL_H_

#include <SDL/SDL.h>

typedef struct Control{
	int left;
	int right;
	int start;
}Control;

Control newControl(int left, int right, int start);

Control createControl(int i){
	Control c;
	switch(i){
		case 0:
			c = newControl(SDLK_LEFT, SDLK_RIGHT, SDLK_SPACE);
			break;

		case 1:
			c = newControl(SDLK_a, SDLK_z, SDLK_e);
			break;

		default:
			break;
	}
	return c;
}

#endif