#include "collide.h"

/**
 * Fonction englobante pour la collision balles - barres
 *                                       balles - briques
 * @param game [description]
 */
void collide(Game *game){
	int i;

	/**
	 * Pour chaque joeur, on teste la collison entre les balles et les barres
	 *                                                   balles et les briques  
	 */
	for(i=0; i<game->nbPlayers; i++){
		barCollide(&game->players[i], game->nbPlayers);
		brickCollide();
	}
}

void barCollide(Player *p, int nbPlayers){
	int i, j, start;

	/* Pour toutes les balles */
	for(i=0; i<nbPlayers; i++){
		/* Si balle dans moitié haute ou basse */
		start = (p[i].ball.center.y > 0) ? 1 : 0;
		printf("j = %d\n", start);

		/* Pour toutes les barres */
		for(j=start; j<nbPlayers; j+=2){
			if(checkBarCollide(&p[i].ball, &p[j].bar) == EXIT_SUCCESS){
				printf("ok\n");
			}
		}
	}

	/*for(i=0; i<nbPlayers; i++){
		if(p->ball.center.x >= p[i].bar.center.x - p[i].bar.width/2 &&
		   p->ball.center.x <= p[i].bar.center.x + p[i].bar.width/2){
			if(p->ball.center.y + p->ball.radius >= p[i].bar.center.y - p[i].bar.height/2 &&
			   p->ball.center.y - p->ball.radius <= p[i].bar.center.y + p[i].bar.height/2){
	
			   p->ball.speed.y *= -1;
			} 
		}
	}*/

}

int checkBarCollide(Ball *ball, Bar *bar){
	/* barres du bas */
	float w = bar->width/2;
	float h = bar->height/2;
	float r = ball->radius;
	if(ball->center.x >= bar->center.x - w && ball->center.x <= bar->center.x + w){
		if(ball->center.y - r <= bar->center.y + h && ball->center.y + r >= bar->center.y - h){
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}

void brickCollide(){

}