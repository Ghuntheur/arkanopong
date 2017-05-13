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
			strcpy(game->level.name, "level/first.txt");
			game->gameState = BUILDING;
			update(game);
			break;

		case BUILDING:
			createPlayers(game);
			if(buildLevel(&game->level) == EXIT_FAILURE){
				printf("Erreur lors de la construction du niveau.\n");
				return;
			};
			game->gameState = PLAYING;
			update(game);
			break;

		case PLAYING:
			play(game);
			break;

		case OVER:
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
			newBall(newPoint(0, 360*pos - 20*pos), newVector(0, 0), newColor(255, 100*i, 50*i)),
			newBar(newPoint(0, 360*pos), newColor(255, 100*i, 50*i)),
			createControl(i),
			i
		);
	}
}

void play(Game *game){
	int loop = 1;
	int i;
  	while(loop){
    	unsigned int startTime = SDL_GetTicks();

    	gameRender(game);
        collide(game);

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
                	for(i=0; i<game->nbPlayers; i++){
                		if(ev.key.keysym.sym == game->players[i].control.left){
                			changeBarSpeed(&game->players[i].bar, CONTROL_LEFT, SPEED_UP);
                		}
                		if(ev.key.keysym.sym == game->players[i].control.right){
                			changeBarSpeed(&game->players[i].bar, CONTROL_RIGHT, SPEED_UP);
                		}
                	}

                    if(ev.key.keysym.sym == SDLK_SPACE){
                    	changeBallSpeed(&game->players[0].ball, 0, SPEED_START);
                    }
                    if(ev.key.keysym.sym == SDLK_e){
                    	changeBallSpeed(&game->players[1].ball, 1, SPEED_START);
                    }
                    break;
 
                case SDL_KEYUP:
                	for(i=0; i<game->nbPlayers; i++){
                		if(ev.key.keysym.sym == game->players[i].control.left){
                			changeBarSpeed(&game->players[i].bar, CONTROL_LEFT, SPEED_STOP);
                		}
                		if(ev.key.keysym.sym == game->players[i].control.right){
                			changeBarSpeed(&game->players[i].bar, CONTROL_RIGHT, SPEED_STOP);
                		}
                	}
                    break;

		        default:
		        	break;
	      	}
	    }
    
    	unsigned int elapsedTime = SDL_GetTicks() - startTime;
    	if(elapsedTime < FRAMERATE_MILLISECONDS){
      		SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    	}
    }
}

void collide(Game *game){
	int i, j, start; 

	for(i=0; i<game->nbPlayers; i++){
		brickCollide(&game->players[i].ball, &game->level);
		
		start = (game->players[i].ball.center.y > 0) ? 1 :0;
		for(j=start; j<game->nbPlayers; j+=2){
			barCollide(&game->players[i].ball, &game->players[j].bar);
		}		
	}
}

void gameRender(Game *game){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	levelRender(&game->level);

	for(i=0; i<game->nbPlayers; i++){
        ballRender(&game->players[i].ball, game->players[i].bar.center.x);
        barRender(&game->players[i].bar);
    }

}
