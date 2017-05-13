#ifndef VARIABLES_H_
#define VARIABLES_H_

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const unsigned int BIT_PER_PIXEL;
extern const unsigned int FRAMERATE_MILLISECONDS;

typedef enum gameState{
	LOADING,
	SELECTING,
	BUILDING,
	PLAYING,
	OVER
}gameState;

typedef enum speed{
	SPEED_START,
	SPEED_UP,
	SPEED_DOWN,
	SPEED_STOP
}speed;

typedef enum brickType{
	FIRST,
	SECOND, 
	THIRD,
	FOURTH
}brickType;

typedef enum controlType{
	CONTROL_LEFT,
	CONTROL_RIGHT,
	CONTROL_START
}controlType;

#endif