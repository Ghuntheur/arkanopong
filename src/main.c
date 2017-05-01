#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include "ball.h"


/**
 * STATIC VARTIABLES
 */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

static const float SCALE_X = 800.;
static const float SCALE_Y = 800.;

void reshape() {
  	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  	gluOrtho2D(-SCALE_X, SCALE_X, -SCALE_Y, SCALE_Y);
}

void setVideoMode() {
	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE)) {
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

  	Ball balle = newBall(newPoint(0, 0), newVector(1, 1), 60, newColor(255, 255, 255));

  	int loop = 1;
  	while(loop) {
    	Uint32 startTime = SDL_GetTicks();

    	glClear(GL_COLOR_BUFFER_BIT);
   		
	    ballDisplay(&balle);

  		SDL_GL_SwapBuffers(); 	

	    SDL_Event ev;
	    while(SDL_PollEvent(&ev)){
	    	if(ev.type == SDL_QUIT){
	    	    loop = 0;
	        	break;
	      	}
	      
	      	switch(ev.type){          
	        	case SDL_VIDEORESIZE:
	          		WINDOW_WIDTH = ev.resize.w;
	          		WINDOW_HEIGHT = ev.resize.h;
	          		setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
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
  
  	return EXIT_SUCCESS;
}