#ifndef MENU_H_
#define MENU_H_

#include <string.h>
#include <dirent.h>
#include "button.h"

typedef struct Menu{
	Button *buttons;
	int base;
	int level;
	int texture;
	int nbButtons;
}Menu;

int buildMenu(Menu *menu);

void getButtonsNumber(Menu *menu, DIR *level, DIR *texture);

int countRepo(DIR *texture);

int countFile(DIR *level);

int allocButtonsMemory(Menu *menu);

int createButtons(Menu *menu);

void menuRender(Menu *menu);

#endif