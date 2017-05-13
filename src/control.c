#include "control.h"

Control newControl(int left, int right, int start){
	Control c;

	c.left  = left;
	c.right = right;
	c.start = start;

	return c;
}
