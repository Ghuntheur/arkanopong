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
			b.texture = newTexture(textureFolder, "2.png");
			break;

		case VS_AI:
			b.center  = newPoint(0, 150);
			b.width   = 400;
			b.height  = 100;
			b.texture = newTexture(textureFolder, "ai.png");
			break; 

		case SUBMIT:
			b.center = newPoint(0, -300);
			b.width   = 700;
			b.height  = 100;
			b.texture = newTexture(textureFolder, "start.png");
			break;
	}
	b.action = type;
	b.buttonSelected = 0;
	b.margin = 0;
	return b;
}

Button newButtonLevelTexture(int type, int length, int i){
	Button b;
	char *textureFolder = "menu/";

	char string[1];
	sprintf(string, "%d", i+1);

	switch(type){
		case LEVEL:
			b.width  = WINDOW_WIDTH/length;
			b.height = 100;
			b.center = newPoint(-WINDOW_WIDTH/2 + b.width*(i+0.5), 0);

			strcpy(b.levelName, "level/");
			strcat(b.levelName, string);
			strcat(b.levelName, ".txt");

			strcpy(b.textureLevel, "lvl");
			strcat(b.textureLevel, string);
			strcat(b.textureLevel, ".png");

			b.texture = newTexture(textureFolder, b.textureLevel);
			break;

		case TEXTURE:
			b.width  = WINDOW_WIDTH/length;
			b.height = 100;
			b.center = newPoint(-WINDOW_WIDTH/2 + b.width*(i+0.5), -150);

			strcpy(b.textureFolder, "textures/");
			strcat(b.textureFolder, string);
			strcat(b.textureFolder, "/");

			b.texture = newTexture(b.textureFolder, "btn.png");
			break;
	}
	b.action = type;
	b.margin = 20;
	b.buttonSelected = 0;
	return b;
}

void drawButton(Button *button){
	float w = button->width/2;
	float h = button->height/2;

	float margin = button->margin;

	float x = button->center.x;
	float y = button->center.y;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, button->texture.memory);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(x-w+margin, y+h); 
		glTexCoord2f(1, 0); glVertex2f(x+w-margin, y+h); 
		glTexCoord2f(1, 1); glVertex2f(x+w-margin, y-h); 
		glTexCoord2f(0, 1); glVertex2f(x-w+margin, y-h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawSelected(Button *button){
	if(button->buttonSelected == 0) return;

	float w = button->width/2;
	float h = button->height/2;

	float x = button->center.x;
	float y = button->center.y;

	float m = button->margin;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, button->selected.memory);

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(x-w+m, y+h); 
		glTexCoord2f(1, 0); glVertex2f(x+w-m, y+h); 
		glTexCoord2f(1, 1); glVertex2f(x+w-m, y-h); 
		glTexCoord2f(0, 1); glVertex2f(x-w+m, y-h); 
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);	
}

void changeButtontexture(Button *button, int nbPlayers){
	char string[1];
	sprintf(string, "%d", nbPlayers);

	button->texture = newTexture("menu/", strcat(string, ".png"));
}

void selectedButton(Button *button){
	button->selected = newTexture("menu/", "selected.png");
	button->buttonSelected = 1;
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
