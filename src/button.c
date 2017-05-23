#include "button.h"

Button newButton(int type){
	Button b;
	char *textureFolder = "menu/";

	switch(type){
		case SUBSTRACT_PLAYER:
			b.center  = newPoint(-300, 300);
			b.width   = 100;
			b.height  = 100;
			b.texture = newTexture(textureFolder, "moins.png");  
			break;

		case ADD_PLAYER:
			b.center  = newPoint(300, 300);
			b.width   = 100;
			b.height  = 100;
			b.texture = newTexture(textureFolder, "plus.png");
			break;

		case PRINT_PLAYER:
			b.center  = newPoint(0, 300);
			b.width   = 400;
			b.height  = 100;
			b.texture = newTexture(textureFolder, "player.jpg");
			break;

		case VS_AI:
			b.center  = newPoint(0, 150);
			b.width   = 400;
			b.height  = 100;
			b.texture = newTexture(textureFolder, "ai.jpg");
			break; 

		case SUBMIT:
			b.center = newPoint(0, -300);
			b.width   = 700;
			b.height  = 100;
			b.texture = newTexture(textureFolder, "start.jpg");
			break;
	}
	b.action = type;
	return b;
}

Button newButtonLevelTexture(int type, int length, int i){
	Button b;
	char *textureFolder = "menu/";

	switch(type){
		case LEVEL:
			b.width  = WINDOW_WIDTH/length;
			b.height = 100;
			b.center = newPoint(-WINDOW_WIDTH/2 + b.width*(i+0.5), 0);
			strcpy(b.levelName, "level/first.txt");
			b.texture = newTexture(textureFolder, "ai.jpg");
			break;

		case TEXTURE:
			b.width  = WINDOW_WIDTH/length;
			b.height = 100;
			b.center = newPoint(-WINDOW_WIDTH/2 + b.width*(i+0.5), -150);
			strcpy(b.textureFolder, "textures/1/");
			b.texture = newTexture(textureFolder, "player.jpg");
			break;
	}
	b.action = type;
	return b;
}

void drawButton(Button *button){
	float w = button->width/2;
	float h = button->height/2;

	float x = button->center.x;
	float y = button->center.y;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, button->texture.memory);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(x-w, y+h); 
		glTexCoord2f(1, 0); glVertex2f(x+w, y+h); 
		glTexCoord2f(1, 1); glVertex2f(x+w, y-h); 
		glTexCoord2f(0, 1); glVertex2f(x-w, y-h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int checkButtonCollide(Button *button, int x, int y){
	transformXY(&x, &y);
	if(x >= button->center.x - button->width/2 &&
	   x <= button->center.x + button->width/2 &&
	   y >= button->center.y - button->height/2 &&
	   y <= button->center.y + button->height/2){
		return button->action;
	}
	return -1;
}

void transformXY(int *x, int *y){
	*x = *x - WINDOW_WIDTH/2;
	*y = -1*(*y) + WINDOW_HEIGHT/2;
}