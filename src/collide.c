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

Box newBoxFromBonus(Bonus *bonus){
	Box b;

	b.center = bonus->center;
	b.width  = bonus->width;
	b.height = bonus->height;

	return b;
}

void barCollide(Ball *ball, Bar *bar, int bonusType){
	if(checkBarCollide(ball, bar) == EXIT_SUCCESS){
		float angle = (ball->center.x - bar->center.x) / (bar->width / 2);
		ball->speed.x += angle;
		ball->speed.y *= -1;
	}
}


int checkBarCollide(Ball *ball, Bar *bar){
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
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;	
}

int checkBoxBoxCollide(Box *A, Box *B){
	if(A->center.x + A->width/2 >= B->center.x - B->width/2 &&
	   A->center.x - A->width/2 <= B->center.x + B->width/2 &&
	   A->center.y + A->height/2 >= B->center.y - B->height/2 &&
	   A->center.y - A->height/2 <= B->center.y + B->height/2){
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

int checkBoxIsOutside(Box *box){
	if(box->center.y + box->height/2 <= -WINDOW_HEIGHT/2 ||
	   box->center.y - box->height/2 >=  WINDOW_HEIGHT/2){
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
				changeBonusId(&level->bricks[i].bonus, ball->id);
				checkBonus(&level->bricks[i]);
			}
			changeBrickLife(&level->bricks[i]);
		}
	}		
}

void bonusCollide(Player *player, Level *level){
	int i;
	for(i=0; i<level->width*level->height; i++){
		if(level->bricks[i].bonus.dropped == 1 && level->bricks[i].bonus.caught != 1){
			Box bonus = newBoxFromBonus(&level->bricks[i].bonus);
			Box boxBar = newBoxFromBar(&player->bar);
			if(checkBoxBoxCollide(&bonus, &boxBar) == EXIT_SUCCESS){
				changeBonusState(&level->bricks[i].bonus, BONUS_CAUGHT);
				applyBonus(player, level->bricks[i].bonus.type);
			}
			else if(checkBoxIsOutside(&bonus) == EXIT_SUCCESS){
				changeBonusState(&level->bricks[i].bonus, BONUS_CAUGHT);
			}
		}
	}
}