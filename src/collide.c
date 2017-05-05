#include "collide.h"

/**
 * Fonction englobante pour la collision balles - barres
 *                                       balles - briques
 * @param game [description]
 */
void collide(Game *game){


	/**
	 * Pour chaque joeur, on teste la collison entre les balles et les barres
	 *                                                   balles et les briques  
	 */
	barCollide(game);
	brickCollide();
}

void barCollide(Game *g){
	int i, j, start;
	float ratio = 10;

	/* Pour toutes les balles */
	for(i=0; i<g->nbPlayers; i++){
		/* Si balle dans moitié haute ou basse */
		start = (g->players[i].ball.center.y > 0) ? 1 : 0;

		/* Pour toutes les barres */
		for(j=start; j<g->nbPlayers; j+=2){
			if(checkBarCollide(&g->players[i].ball, &g->players[j].bar, &ratio) == EXIT_SUCCESS){
				g->players[i].ball.speed.y *= -1;
			}
		}
	}
}

int checkBarCollide(Ball *ball, Bar *bar, float *ratio){
	/* barres du bas */
	float w = bar->width/2;
	float h = bar->height/2;
	float r = ball->radius;
	if(ball->center.x >= bar->center.x - w && ball->center.x <= bar->center.x + w){
		if(ball->center.y - r <= bar->center.y + h && ball->center.y + r >= bar->center.y - h){
			/* calcul du ratio */
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}
	return EXIT_FAILURE;
}

void brickCollide(){

}