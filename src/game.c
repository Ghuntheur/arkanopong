#include "game.h"

Game newGame(){
	Game g;
	g.gameState = LOADING;
	return g;
}

void update(Game *game){

	switch(game->gameState){
		case LOADING:
			if(initSDL() == EXIT_FAILURE) return;
			game->gameState = SELECTING;
			update(game);
			break;

		case SELECTING:
			/**
			 * Menu : 
			 * nb joueurs
			 * niveau
			 * textures
			 * IA 
			 */
			game->gameState = BUILDING;
			update(game);
			break;

		case BUILDING:
			createPlayers(game);
			game->gameState = PLAYING;
			update(game);
			break;

		case PLAYING:
			play(game);
			break;

		default:
			break;
	}
}

void createPlayers(Game *game){
	int i, pos;

	/*Allocation mémoires*/
	game->nbPlayers = 2;
	game->players = (Player*) malloc(game->nbPlayers*sizeof(Player));
	if(game->players == NULL) return;

	for(i=0; i<game->nbPlayers; i++){
		pos = (i%2 == 0) ? -1 : 1;
		game->players[i] = newPlayer(
			newBall(newPoint(0, 360*pos - 20*pos), newVector(1, 2*i+1), newColor(255, 100*i, 50*i)),
			newBar(newPoint(0, 360*pos), newColor(255, 100*i, 50*i)),
			i
		);
	}
}

void play(Game *game){
	int loop = 1;
  	while(loop){
    	Uint32 startTime = SDL_GetTicks();

    	gameRender(game);
        /*collide(&game);*/

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
                        barMove(&game->players[0].bar, ev.key.keysym.sym);
                    }
                    if(ev.key.keysym.sym == SDLK_a || ev.key.keysym.sym == SDLK_z){
                        barMove(&game->players[1].bar, ev.key.keysym.sym);
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
}

void gameRender(Game *game){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	for(i=0; i<game->nbPlayers; i++){
        ballRender(&game->players[i].ball);
        barDraw(&game->players[i].bar);
    }
}
