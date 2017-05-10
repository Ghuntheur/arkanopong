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

		/*case PLAYING:
			play(game);
			break;

		default:
			break;
	*/}
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
			newBar(newPoint(0, 360*pos), newColor(25, 100*i, 50*i)),
			i
		);
	}
}

void play(Game *game){
	printf("ok\n");
}

void gameRender(Game *game){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	for(i=0; i<game->nbPlayers; i++){
        ballRender(&game->players[i].ball);
        barDraw(&game->players[i].bar);
    }
}
