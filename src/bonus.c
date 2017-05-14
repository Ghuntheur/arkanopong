#include "bonus.h"

Bonus newBonus(int value, Point center){
	Bonus b;

	b.type    = value;
	b.center  = center;
	b.width   = 16;
	b.height  = 32;
	b.dropped = 0;
	b.caught  = 0;

	return b;
}


