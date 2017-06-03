#include "game.h"

Game newGame(){
	Game g;
	g.gameState = LOADING;
	g.nbPlayers = 2;
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
			if(buildMenu(&game->menu) == EXIT_FAILURE){
				printf("Erreur lors de la construction du menu\n");
				return;
			}
			playMenu(game);
			break;

		case BUILDING:
			createPlayers(game);
			if(buildLevel(&game->level, game->textureFolder) == EXIT_FAILURE){
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
			printf("Game Over\n");
			/*Appel du menu*/
			break;

		default:
			break;
	}
}

void createPlayers(Game *game){
	int i, pos;

	/*Allocation mémoires*/
	game->players = (Player*) malloc(game->nbPlayers*sizeof(Player));
	if(game->players == NULL) return;

	for(i=0; i<game->nbPlayers; i++){
		pos = (i%2 == 0) ? -1 : 1;
		game->players[i] = newPlayer(
			newBall(newPoint(0, 360*pos - 20*pos), newVector(0, 0), newTexture(game->textureFolder, "ball.png"), i),
			newBar(newPoint(0, 360*pos), newTexture(game->textureFolder, "bar.png"), i),
			createControl(i),
			newTexture(game->textureFolder, "life.png"),
			i
		);
	}
}

void playMenu(Game *game){
	int loop = 1, key;
	while(loop){
		unsigned int startTime = SDL_GetTicks();

		menuRender(&game->menu);

		SDL_GL_SwapBuffers();

		SDL_Event ev;
		while(SDL_PollEvent(&ev)){

			switch(ev.type){
				case SDL_MOUSEBUTTONDOWN:
					key = ev.button.button;
					if(key == SDL_BUTTON_LEFT){
						buttonCollide(game, ev.motion.x, ev.motion.y);
					}
					break;

				case SDL_QUIT:
					loop = 0;
					break;
			}
		}

		unsigned int elapsedTime = SDL_GetTicks() - startTime;
    	if(elapsedTime < FRAMERATE_MILLISECONDS){
      		SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
    	}
	}
}

void play(Game *game){
	int loop = 1;
	int i, key;
  	while(loop){
    	unsigned int startTime = SDL_GetTicks();

    	gameRender(game);
        collide(game);
        loseBall(game);

  		SDL_GL_SwapBuffers();

	    SDL_Event ev;
	    while(SDL_PollEvent(&ev)){
	    	if(ev.type == SDL_QUIT){
	    	    loop = 0;
	        	break;
	      	}

	      	switch(ev.type){          
	        	
                case SDL_KEYDOWN:
                	key = ev.key.keysym.sym;
                	for(i=0; i<game->nbPlayers; i++){
                		if(key == game->players[i].control.left){
                			changeBarSpeed(&game->players[i].bar, CONTROL_LEFT, SPEED_UP);
                		}
                		if(key == game->players[i].control.right){
                			changeBarSpeed(&game->players[i].bar, CONTROL_RIGHT, SPEED_UP);
                		}
                		if(key == game->players[i].control.start){
                			changeBallSpeed(&game->players[i].ball, SPEED_START);
                		}
                	}
                    break;
 
                case SDL_KEYUP:
                	key = ev.key.keysym.sym;
                	for(i=0; i<game->nbPlayers; i++){
                		if(key == game->players[i].control.left){
                			changeBarSpeed(&game->players[i].bar, CONTROL_LEFT, SPEED_STOP);
                		}
                		if(key == game->players[i].control.right){
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
		bonusCollide(&game->players[i], &game->level);
		
		start = (game->players[i].ball.center.y > 0) ? 1 :0;
		for(j=start; j<game->nbPlayers; j+=2){
			barCollide(&game->players[i].ball, &game->players[j].bar);
		}		
	}
}

void buttonCollide(Game *game, int x, int y){
	int i, action;
	for(i=0; i<game->menu.nbButtons; i++){
		if((action = checkButtonCollide(&game->menu.buttons[i], x, y)) != -1){
			applyAction(game, &game->menu.buttons[i]);
			if(action == SUBSTRACT_PLAYER || action == ADD_PLAYER){
				changeButtontexture(&game->menu.buttons[PRINT_PLAYER], game->nbPlayers);
			}
		}
	}
}

void applyAction(Game *game, Button *button){
	switch(button->action){
		case ADD_PLAYER:
			if(game->nbPlayers+1 <= MAX_PLAYERS)
				game->nbPlayers += 2;			
			break;

		case SUBSTRACT_PLAYER:
			if(game->nbPlayers > 2)
				game->nbPlayers -= 2;
			break;

		case LEVEL:
			strcpy(game->level.name, button->levelName);
			break;

		case TEXTURE:
			strcpy(game->textureFolder, button->textureFolder);
			break;

		case SUBMIT:
			game->gameState = BUILDING;
			update(game);
			break;
	}
}

void gameRender(Game *game){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	levelRender(&game->level);

	for(i=0; i<game->nbPlayers; i++){
        ballRender(&game->players[i].ball, game->players[i].bar.center.x, game->players[i].bar.width);
        barRender(&game->players[i].bar);
        lifeRender(&game->players[i], &game->players[i].bar);
        checkDisableBonus(&game->players[i]);
    }
}

void loseBall(Game *game){
	int i, pos;
	for(i=0; i<game->nbPlayers; i++){
		if(game->players[i].ball.lost == 1){
			if(game->players[i].life > 1){
				changePlayerLife(&game->players[i], LOOSE_LIFE);
				printf("%d lifes left for player %d\n", game->players[i].life, game->players[i].id);
				pos = (i%2 == 0) ? -1 : 1;
				game->players[i].ball = newBall(newPoint(0, 360*pos - 20*pos), newVector(0, 0), newTexture(game->textureFolder, "ball.png"), i);
			}
			else{
				printf("This is the end, player n%d\n", game->players[i].id);
				game->gameState = OVER;
				update(game);
			}
		}
	}
}