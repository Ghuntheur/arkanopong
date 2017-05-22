#include "brick.h"

Brick newBrick(int value, int width, int height, int i, int j, char *textureFolder){
	Brick b;

	b.life    = value/10;
	
	b.broken  = 0;
	
	b.width  = WINDOW_WIDTH/width;
	b.height = 20;

	b.center = newPoint(
		-WINDOW_WIDTH/2 + b.width*(i+0.5),
		WINDOW_HEIGHT/2 - (WINDOW_HEIGHT-height*b.height)/2 - b.height*(j+0.5)
	);

	b.bonus = newBonus(value%10, b.center, textureFolder);
	b.texture = newTexture(textureFolder, texturizeBrick(b.life));

	return b;
}

char *texturizeBrick(int type){
	switch(type){
		case SIMPLE:
			return  "simple.jpg";
			break;
		
		case DOUBLE:
			return  "double.jpg";
			break;

		case TRIPLE:
			return "triple.jpg";
			break;

		case UNBREAKABLE:
			return "unbreakable.jpg";
			break;

		default:
			return "simple.jpg";
			break;
	}
}

void drawBrick(Brick *brick){
	float w = brick->width/2;
	float h = brick->height/2;

	float x = brick->center.x;
	float y = brick->center.y;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, brick->texture.memory);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(x-w, y+h); 
		glTexCoord2f(1, 0); glVertex2f(x+w, y+h); 
		glTexCoord2f(1, 1); glVertex2f(x+w, y-h); 
		glTexCoord2f(0, 1); glVertex2f(x-w, y-h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void changeBrickLife(Brick *brick){
	if(brick->life == UNBREAKABLE) return;
	brick->life--;
	if(checkBrickIsAlive(brick->life) == EXIT_FAILURE){
		brick->broken = 1;
	}
}

int checkBrickIsAlive(int life){
	return (life > 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void checkBonus(Brick *brick){
	int i;
	for(i=BONUS_EMPTY+1; i<numberOfBonus; i++){
		if(brick->life == i && brick->bonus.type != 0){
			changeBonusState(&brick->bonus, BONUS_DROPPED);
			return;			
		}
	}
}