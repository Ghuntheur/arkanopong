#ifndef VARIABLES_H_
#define VARIABLES_H_

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const unsigned int BIT_PER_PIXEL;
extern const Uint32 FRAMERATE_MILLISECONDS;

typedef enum gameState{
	LOADING,
	SELECTING,
	BUILDING,
	PLAYING,
	OVER
}gameState;

typedef enum speed{
	SPEED_UP,
	SPEED_DOWN,
	SPEED_STOP
}speed;

#endif