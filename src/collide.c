#include "collide.h"

void collide(Game *game){
	int i, nbPlayers = game->nbPlayers;

	for(i=0; i<nbPlayers; i++){
		barCollide(&game->players[i], nbPlayers);
		brickCollide();
	}	
}

void barCollide(Player *p, int nbPlayers){
	int i;
	for(i=0; i<nbPlayers; i++){
		if(p->ball.center.x >= p[i].bar.center.x - p[i].bar.width/2 &&
		   p->ball.center.x <= p[i].bar.center.x + p[i].bar.width/2){
			if(p->ball.center.y + p->ball.radius >= p[i].bar.center.y - p[i].bar.height/2 &&
			   p->ball.center.y - p->ball.radius <= p[i].bar.center.y + p[i].bar.height/2){
	
			   p->ball.speed.y *= -1;
			} 
		}
	}
}

void brickCollide(){

}