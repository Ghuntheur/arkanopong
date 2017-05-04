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
	float ratio = 10;

	/* Pour toutes les balles */
	for(i=0; i<nbPlayers; i++){
		/* Si balle dans moitié haute ou basse */
		start = (p[i].ball.center.y > 0) ? 1 : 0;

		/* Pour toutes les barres */
		for(j=start; j<nbPlayers; j+=2){
			if(checkBarCollide(&p[i].ball, &p[j].bar, &ratio) == EXIT_SUCCESS){
				p[i].ball.speed.y *= -1;
			}
		}
	}
}

int checkBarCollide(Ball *ball, Bar *bar, float *ratio){
	/* barress du bas */
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