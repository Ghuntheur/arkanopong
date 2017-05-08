#ifndef VARIABLES_H_
#define VARIABLES_H_

#include <SDL/SDL.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const unsigned int BIT_PER_PIXEL;
extern const Uint32 FRAMERATE_MILLISECONDS;

typedef enum gameState{
	LOADING,
	BUILDING,
	PLAYING,
	OVER
}gameState;

#endif