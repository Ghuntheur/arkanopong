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
		/*barCollide(&game->players[i], game->nbPlayers);*/
		brickCollide(&game->players[i].ball, &game->level);
	}
}

Box newBoxFromBall(Ball *ball){
	Box b;

	b.center = ball->center;
	b.width  = ball->radius;
	b.height = ball->radius;

	return b;
}

Box newBoxFromBrick(Brick *brick){
	Box b;

	b.center = brick->center;
	b.width  = brick->width;
	b.height = brick->height;

	return b;
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
	return EXIT_SUCCESS;	
}

int checkBoxBoxCollide(Box *ball, Box *box){
	return EXIT_SUCCESS;
}

void brickCollide(Ball *ball, Level *level){
	int i;
	for(i=0; i<level->width*level->height; i++){
		Box boxBall = newBoxFromBall(ball);
		Box box     = newBoxFromBrick(&level->bricks[i]);
		if(checkBoxBoxCollide(&boxBall, &box) == EXIT_FAILURE) return;
	}
}