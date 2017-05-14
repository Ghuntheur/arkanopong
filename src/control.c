#include "control.h"

Control newControl(int left, int right, int start){
	Control c;

	c.left  = left;
	c.right = right;
	c.start = start;

	return c;
}

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