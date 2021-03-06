#ifndef BUTTON_H_
#define BUTTON_H_

#include "geometry.h"
#include "texture.h"
#include "variables.h"

typedef struct Button{
	Point center;
	float width;
	float height;
	float margin;
	int action;
	int buttonSelected;
	char levelName[100];
	char textureFolder[100];
	char textureLevel[100];

	Texture texture;
	Texture selected;
	
}Button;

Button newButton(int type);

Button newButtonLevelTexture(int type, int length, int i);

void transformXY(int *x, int *y);

void drawButton(Button *button);

void drawSelected(Button *button);

void changeButtontexture(Button *button, int nbPlayers);

void selectedButton(Button *button);

int checkButtonCollide(Button *button, int x, int y);

#endif
