#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "init.h"
#include "ball.h"
#include "bar.h"
#include "player.h"
#include "game.h"
#include "collide.h"

int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

int main(int argc, char** argv) {
  
  	if(initSDL() == EXIT_FAILURE) return EXIT_FAILURE;     	

    Game game;
    if(newGame(&game, 2) == EXIT_FAILURE) return EXIT_FAILURE;
  	
  	int loop = 1;
  	while(loop){
    	Uint32 startTime = SDL_GetTicks();

    	glClear(GL_COLOR_BUFFER_BIT);

        gameRender(&game);
        collide(&game);

  		SDL_GL_SwapBuffers();

	    SDL_Event ev;
	    while(SDL_PollEvent(&ev)){
	    	if(ev.type == SDL_QUIT){
	    	    loop = 0;
	        	break;
	      	}

	      	switch(ev.type){          
	        	
                /**
                 * TODO: LAISSER TOUCHE ENFONCEE
                 */
                case SDL_KEYDOWN:
                    if(ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_RIGHT){
                        barMove(&game.players[0].bar, ev.key.keysym.sym);
                    }
                    if(ev.key.keysym.sym == SDLK_a || ev.key.keysym.sym == SDLK_z){
                        barMove(&game.players[1].bar, ev.key.keysym.sym);
                    }
                    break;

		        default:
		        	break;
	      	}
	    }
    
    	Uint32 elapsedTime = SDL_GetTicks() - startTime;
    	if(elapsedTime < FRAMERATE_MILLISECONDS){
      		SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    	}
  	}
  
  	SDL_Quit();
  
    printf(" succ %d\n", EXIT_SUCCESS);

  	return EXIT_SUCCESS;
}