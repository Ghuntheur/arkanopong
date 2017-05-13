#include "collide.h"

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
	if(ball->center.x + ball->width >= box->center.x - box->width &&
	   ball->center.x - ball->width <= box->center.x + box->width &&
	   ball->center.y + ball->height >= box->center.y - box->height &&
	   ball->center.y - ball->height <= box->center.y + box->height){
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int checkCornersInCircle(Ball *ball, Box *box){
	int x = box->center.x;
	int y = box->center.y;
	int w = box->width / 2;
	int h = box->height / 2;

	if(checkPointInCircle(x-w, y+h, ball) == EXIT_SUCCESS ||
	   checkPointInCircle(x+w, y+h, ball) == EXIT_SUCCESS ||
	   checkPointInCircle(x+w, y-h, ball) == EXIT_SUCCESS ||
	   checkPointInCircle(x-w, y-h, ball) == EXIT_SUCCESS){
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int checkPointInCircle(int x, int y, Ball *ball){
	int dist = (x-ball->center.x)*(x-ball->center.x) + (y-ball->center.y)*(y-ball->center.y);
	return (dist > ball->radius*ball->radius) ? EXIT_FAILURE : EXIT_SUCCESS;
}

int checkPointInBox(Point *center, Box *box){
	if(center->x >= box->center.x - box->width &&
	   center->x <= box->center.x + box->width &&
	   center->y >= box->center.y - box->height &&
	   center->y <= box->center.y + box->height){
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int checkThrown(Vector *AC, Vector *AB, Vector *BC){
	int s1 = dotProduct(AC, AB);
	int s2 = dotProduct(BC, AB);

	return (s1*s2 > 0) ? EXIT_FAILURE : EXIT_SUCCESS; 
}

void brickCollide(Ball *ball, Level *level){
	int i;
	for(i=0; i<level->width*level->height; i++){
		Box boxBall = newBoxFromBall(ball);
		Box box     = newBoxFromBrick(&level->bricks[i]);
		/**
		 * Test de collision entre les boites engendrées par la balle et la brique
		 */
		if(checkBoxBoxCollide(&boxBall, &box) == EXIT_FAILURE) continue;

		/**
		 * Test de collision entre un sommet de la brique et la balle
		 */
		if(checkCornersInCircle(ball, &box) == EXIT_SUCCESS){
			if(level->bricks[i].broken != 1)
				printf("brick %d is broken with test 1\n", i);
			level->bricks[i].broken = 1;
		}

		/**
		 * Si balle est dans le cercle
		 */
		if(checkPointInBox(&ball->center, &box) == EXIT_SUCCESS){
			if(level->bricks[i].broken != 1)
				printf("brick %d is broken with test 2\n", i);
			level->bricks[i].broken = 1;
		}

		/**
		 *  Projeté du centre de la balle sur les segments de la briques
		 */
		Point A = newPoint(box.center.x-box.width/2, box.center.y+box.height/2);
		Point B = newPoint(box.center.x+box.width/2, box.center.y+box.height/2);
		Point C = box.center;
		Point D = newPoint(box.center.x-box.width/2, box.center.y-box.height/2);

		Vector AC = newVectorFromPoint(&A, &C);
		Vector AB = newVectorFromPoint(&A, &B);
		Vector BC = newVectorFromPoint(&B, &C);
		Vector DC = newVectorFromPoint(&D, &C);
		Vector AD = newVectorFromPoint(&A, &D);

		if(checkThrown(&AC, &AB, &BC) == EXIT_SUCCESS || checkThrown(&AC, &AD, &DC) == EXIT_SUCCESS){
			if(level->bricks[i].broken != 1)
				printf("brick %d is broken with test 3\n", i);
			level->bricks[i].broken = 1;
		}
	}
}