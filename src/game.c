#include "game.h"

int newGame(Game *game, int nbPlayers){


	game->nbPlayers = nbPlayers;
	game->players = (Player*) malloc(game->nbPlayers*sizeof(Player));
	if(game->players == NULL) return EXIT_FAILURE;

	game->players[0] = newPlayer(
			newBall(newPoint(0, 0), newVector(0, -3), 30, newColor(255, 0, 0)),
			newBar(newPoint(-200, -360), 100, 20, newColor(255, 0, 0)),
			0
		);

	game->players[1] = newPlayer(
        	newBall(newPoint(0, 0), newVector(2, 3), 30, newColor(0, 255, 0)),
        	newBar(newPoint(-200, 360), 100, 20, newColor(0, 255, 0)),
        	1
        );

	game->players[2] = newPlayer(
        	newBall(newPoint(0, 0), newVector(-1, 1), 30, newColor(0, 255, 255)),
        	newBar(newPoint(200, -360), 100, 20, newColor(0, 255, 255)),
        	2
        );

	game->players[3] = newPlayer(
        	newBall(newPoint(0, 0), newVector(2, -1), 30, newColor(255, 255, 0)),
        	newBar(newPoint(200, 360), 100, 20, newColor(255, 255, 0)),
        	3
        );

	return EXIT_SUCCESS;
}


void gameRender(Game *game){
	int i;

	for(i=0; i<game->nbPlayers; i++){
        ballRender(&game->players[i].ball);
        barDraw(&game->players[i].bar);
    }
}
