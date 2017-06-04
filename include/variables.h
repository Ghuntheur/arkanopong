#ifndef VARIABLES_H_
#define VARIABLES_H_

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

extern const unsigned int BIT_PER_PIXEL;
extern const unsigned int FRAMERATE_MILLISECONDS;

extern const unsigned int BONUS_DURATION;

extern const int MAX_PLAYERS;

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
	BONUS_EMPTY,  		/*0*/	

	BAR_BIGGER,         /*1*/
	BALL_SPEED_DOWN, 	/*2*/
	BALL_SIZE_UP,		/*3*/
	WIN_LIFE,			/*4*/
	INVINCIBLE,			/*5*/

	BAR_SMALLER,		/*6*/
	BALL_SPEED_UP,		/*7*/
	LOOSE_LIFE,			/*8*/
	BAR_CLOSER,			/*9*/

	BAR_FURTHER,		/* enlever bonus */
	BALL_SIZE_DOWN,		/* enlever bonus */

	numberOfBonus
}bonusType;

typedef enum bonusState{
	BONUS_DROPPED,
	BONUS_CAUGHT
}bonusState;

typedef enum buttonType{
	SUBSTRACT_PLAYER,
	ADD_PLAYER,
	PRINT_PLAYER,
	VS_AI,
	SUBMIT,
	LEVEL,
	TEXTURE,
}buttonType;


#endif