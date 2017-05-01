#include "game.h"

Game newGame(int nbPlayers){
	Game game;
	int i;

	game.nbPlayers = nbPlayers;
	game.players = (Player *) malloc(game.nbPlayers*sizeof(Player));
	if(game.players != NULL){
		for(i=0; i<game.nbPlayers; i++){
			game.players[i] = newPlayer(newBall(newPoint(0, -300), newVector(2, 1), 30, newColor(255, 0, 0)),
       									newBar(newPoint(0, -360), 100, 20, newColor(255, 0, 0))
       									);
		}
	}

	return game;
}