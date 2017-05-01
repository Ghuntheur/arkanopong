#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

/**
 * STATIC VARTIABLES
 */
static unsigned int WINDOW_WIDTH = 800;
static unsigned int WINDOW_HEIGHT = 800;
static const unsigned int BIT_PER_PIXEL = 32;
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

void reshape() {
  	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  	gluOrtho2D(-1., 1., -1., 1.);
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

  	int loop = 1;
  	while(loop) {
    	Uint32 startTime = SDL_GetTicks();

   /* 	glClear(GL_COLOR_BUFFER_BIT);

	    glColor3ub(255, 0, 0);

	    glPushMatrix();
	    glScalef(0.3f, 0.3f, 0.3f);

	    glPopMatrix();

   

  		SDL_GL_SwapBuffers();*/
	    /* ****** */    

	    SDL_Event e;
	    while(SDL_PollEvent(&e)) {
	    	if(e.type == SDL_QUIT) {
	    	    loop = 0;
	        	break;
	      	}
	      
	      	switch(e.type) {          
	        	case SDL_VIDEORESIZE:
	          		WINDOW_WIDTH = e.resize.w;
	          		WINDOW_HEIGHT = e.resize.h;
	          		setVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT);
	          		break;

	        	/*case SDL_KEYDOWN:
			        if (e.key.keysym.sym == 'q' || e.key.keysym.sym == SDLK_ESCAPE) {
			    	    loop = 0;
			        }
			        break;
		        */
		       
		        default:
		        	break;
	      	}
	    }
    
    	Uint32 elapsedTime = SDL_GetTicks() - startTime;
    	if(elapsedTime < FRAMERATE_MILLISECONDS) {
      		SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    	}
  	}
  
  	SDL_Quit();
  
  	return EXIT_SUCCESS;
}