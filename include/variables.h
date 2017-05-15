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
	EMPTY,
	SIMPLE, 
	DOUBLE,
	TRIPLE,
	UNBREAKABLE,
}brickType;

typedef enum controlType{
	CONTROL_LEFT,
	CONTROL_RIGHT,
	CONTROL_START
}controlType;

typedef enum bonusType{
	bonusStart,
	BAR_BIGGER,
	BAR_STICKY,
	BALL_SPEED_DOWN,
	BALL_BIGGER,
	numberOfBonus
}bonusType;

typedef enum bonusState{
	BONUS_DROPPED,
	BONUS_CAUGHT
}bonusState;

#endif