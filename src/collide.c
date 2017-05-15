#include "collide.h"

Box newBoxFromBall(Ball *ball){
	Box b;

	b.center = ball->center;
	b.width  = ball->radius*2;
	b.height = ball->radius*2;

	return b;
}

Box newBoxFromBrick(Brick *brick){
	Box b;

	b.center = brick->center;
	b.width  = brick->width;
	b.height = brick->height;

	return b;
}

Box newBoxFromBar(Bar *bar){
	Box b;

	b.center = bar->center;
	b.width  = bar->width;
	b.height = bar->height;

	return b;
}

void barCollide(Ball *ball, Bar *bar){
	float ratio;
	if(checkBarCollide(ball, bar, &ratio) == EXIT_SUCCESS){
		ball->speed.y *= -1;	
	}
}


int checkBarCollide(Ball *ball, Bar *bar, float *ratio){
	Box boxBall = newBoxFromBall(ball);
	Box box     = newBoxFromBar(bar);
	/**
	 * Test de collision entre les boites engendrées par la balle et la brique
	 */
	if(checkBoxBoxCollide(&boxBall, &box) == EXIT_FAILURE) return EXIT_FAILURE;

	/**
	 * Test de collision entre un sommet de la brique et la balle
	 */
	if(checkCornersInCircle(ball, &box) == EXIT_SUCCESS) return EXIT_SUCCESS;

	/**
	 * Si balle est dans le brique
	 */
	if(checkPointInBox(&ball->center, &box) == EXIT_SUCCESS) return EXIT_SUCCESS;

	/**
	 *  Projeté du centre de la balle sur les segments de la brique
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
		ball->speed.y *= -1;
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;	
}

int checkBoxBoxCollide(Box *ball, Box *box){
	if(ball->center.x + ball->width/2 >= box->center.x - box->width/2 &&
	   ball->center.x - ball->width/2 <= box->center.x + box->width/2 &&
	   ball->center.y + ball->height/2 >= box->center.y - box->height/2 &&
	   ball->center.y - ball->height/2 <= box->center.y + box->height/2){
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int checkCornersInCircle(Ball *ball, Box *box){
	int x = box->center.x;
	int y = box->center.y;
	int w = box->width/2;
	int h = box->height/2;

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

int checkBrickCollide(Ball *ball, Brick *brick){
	Box boxBall = newBoxFromBall(ball);
	Box box     = newBoxFromBrick(brick);
	/**
	 * Test de collision entre les boites engendrées par la balle et la brique
	 */
	if(checkBoxBoxCollide(&boxBall, &box) == EXIT_FAILURE) return EXIT_FAILURE;

	/**
	 * Test de collision entre un sommet de la brique et la balle
	 */
	if(checkCornersInCircle(ball, &box) == EXIT_SUCCESS) return EXIT_SUCCESS;

	/**
	 * Si balle est dans le brique
	 */
	if(checkPointInBox(&ball->center, &box) == EXIT_SUCCESS) return EXIT_SUCCESS;
	

	/**
	 *  Projeté du centre de la balle sur les segments de la brique
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

	if(checkThrown(&AC, &AB, &BC) == EXIT_SUCCESS || checkThrown(&AC, &AD, &DC) == EXIT_SUCCESS) return EXIT_SUCCESS;

	return EXIT_FAILURE;
}

int checkBrickCollideBySide(Ball *ball, Box *box){
	if(ball->center.y < box->center.y+box->height/2 &&
	   ball->center.y > box->center.y-box->height/2){
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

void brickCollide(Ball *ball, Level *level){
	int i;
	for(i=0; i<level->width*level->height; i++){
		if(checkBrickCollide(ball, &level->bricks[i]) == EXIT_SUCCESS){
			if(level->bricks[i].broken == 0){
				Box box = newBoxFromBrick(&level->bricks[i]);
				if(checkBrickCollideBySide(ball, &box) == EXIT_SUCCESS){
					ball->speed.x *= -1;
				}else{
					ball->speed.y *= -1;
				}
				changeBonusDirection(&level->bricks[i].bonus, ball->id%2);
				checkBonus(&level->bricks[i]);
			}
			level->bricks[i].broken = 1;
		}
	}		
}