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
		case 2:
			c = newControl(SDLK_i, SDLK_o, SDLK_p);
			break;
		case 3:
			c = newControl(SDLK_w, SDLK_x, SDLK_c);
			break;
		case 4:
			c = newControl(SDLK_KP1, SDLK_KP2, SDLK_KP3);
			break;
		case 5:
			c = newControl(SDLK_INSERT, SDLK_HOME, SDLK_PAGEUP);
			break;
		default:
			break;
	}
	return c;
}