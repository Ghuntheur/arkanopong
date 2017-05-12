#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "variables.h"
#include "init.h"
#include "game.h"
#include "player.h"
#include "ball.h"
#include "bar.h"
#include "collide.h"
#include "level.h"
#include "brick.h"

int main(int argc, char** argv){

    Game game = newGame();	 	

    update(&game);

  	return EXIT_SUCCESS;
}