#include "menu.h"

int buildMenu(Menu *menu){

	DIR *level = opendir("level");
	DIR *texture = opendir("textures");
	if(level == NULL || texture == NULL) return EXIT_FAILURE;
	getButtonsNumber(menu, level, texture);
	if(allocButtonsMemory(menu) == EXIT_FAILURE) return EXIT_FAILURE;
	if(createButtons(menu) == EXIT_FAILURE) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

void getButtonsNumber(Menu *menu, DIR *level, DIR *texture){
	menu->base = 5;
	menu->level = countFile(level);
	menu->texture = countRepo(texture);
	menu->nbButtons = menu->base + menu->texture + menu->level;
}

int countRepo(DIR *texture){
	int count = 0;
	struct dirent *ent = NULL;

	while((ent = readdir(texture)) != NULL){
		if(strchr(ent->d_name, '.') == NULL)
			count++;
	}
	return count;
}

int countFile(DIR *level){
	int count = 0;
	struct dirent *ent = NULL;

	while((ent = readdir(level)) != NULL){
		if(strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
			count++;
	}
	return count;
}

int allocButtonsMemory(Menu *menu){
	menu->buttons = (Button*) malloc(menu->nbButtons*sizeof(Button));
	if(menu->buttons == NULL) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int createButtons(Menu *menu){
	int i;
	for(i=0; i<menu->nbButtons; i++){
		if(i >= LEVEL && i < LEVEL+menu->level){
			menu->buttons[i] = newButtonLevelTexture(LEVEL, menu->level, menu->base+menu->level-i-1);
		}else if(i >= TEXTURE && i <= TEXTURE+menu->texture){
			menu->buttons[i] = newButtonLevelTexture(TEXTURE, menu->texture, menu->base+menu->level+menu->texture-i-1);
		}else{
			menu->buttons[i] = newButton(i);
		}		
	}
	return EXIT_SUCCESS;
}

void menuRender(Menu *menu){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);

	for(i=0; i<menu->nbButtons; i++){
		drawButton(&menu->buttons[i]);
	}	
}