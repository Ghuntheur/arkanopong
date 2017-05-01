#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "ball.h"
#include "bar.h"

/**
 * VARIABLES GLOBALES A TOUS LES FICHIERS
 */
int WINDOW_WIDTH = 800;
int WINDOW_HEIGHT = 800;

/**
 * VARIABLES GLOABLES POUR MAIN
 */
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape() {
  	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  	gluOrtho2D(-WINDOW_WIDTH/2, WINDOW_WIDTH/2, -WINDOW_HEIGHT/2, WINDOW_HEIGHT/2);
}

void setVideoMode() {
	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL)) {
    	fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
    	exit(EXIT_FAILURE);
  	}
  
  	reshape();
}


int main(int argc, char** argv) {
  
  	if(SDL_Init(SDL_INIT_VIDEO) == -1){
      fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
    	return EXIT_FAILURE;
  	}
   
  	setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);

  	SDL_WM_SetCaption("Arkanopong", NULL);

  	Ball balle = newBall(newPoint(0, 0), newVector(1, 0), 30, newColor(255, 255, 255));
    Bar barre  = newBar(newPoint(0, -360), 100, 20, newColor(50, 50, 50));

  	int loop = 1;
  	while(loop){
    	Uint32 startTime = SDL_GetTicks();

    	glClear(GL_COLOR_BUFFER_BIT);
   		
	    ballRender(&balle);
        barDraw(&barre);        

  		SDL_GL_SwapBuffers(); 

        SDL_EnableKeyRepeat(1, 2);

        /* Répétition des touches*/
       	

	    SDL_Event ev;
	    while(SDL_PollEvent(&ev)){
	    	if(ev.type == SDL_QUIT){
	    	    loop = 0;
	        	break;
	      	}

	      	switch(ev.type){          
	        	
                /**
                 * TODO: LAISSE TOUCHE ENFONCEE
                 */
                case SDL_KEYDOWN:
                    if(ev.key.keysym.sym == SDLK_LEFT || ev.key.keysym.sym == SDLK_RIGHT){
                        barMove(&barre, ev.key.keysym.sym);
                    }
                    break;

                case 

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
  
  	return EXIT_SUCCESS;
}