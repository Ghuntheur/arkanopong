#include "level.h"

int buildLevel(Level *level, char *textureFolder){
	FILE *file = initLevel(level);
	if(file == NULL) return EXIT_FAILURE;
	if(allocBricksMemory(level) == EXIT_FAILURE) return EXIT_FAILURE;
	if(createBricks(level, file, textureFolder) == EXIT_FAILURE) return EXIT_FAILURE;
	level->texture = newTexture(textureFolder, "bgd.png");
	
	return EXIT_SUCCESS;
}

FILE *initLevel(Level *level){
	FILE *file = fopen(level->name, "r");
	if(file == NULL) return NULL;

	/**
	 * Récupération de la largeur, hauteur du niveau
	 */
	fscanf(file, "%d %d", &level->width, &level->height);

	return file;
}

/**
 * Allocation mémoire
 */
int allocBricksMemory(Level *level){
	level->bricks = (Brick*) malloc(level->width * level->height * sizeof(Brick));
	if(level->bricks == NULL) return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int createBricks(Level *level, FILE *file, char *textureFolder){
	int i, j, num, count = 0;
	for(j=0; j<level->height; j++){
		for(i=0; i<level->width; i++){
			fscanf(file, "%d ", &num);
			level->bricks[count] = newBrick(num, level->width, level->height, i, j, textureFolder);
			count++;
		}
	}

	fclose(file);	
	return EXIT_SUCCESS;
}

void backgroundRender(Level *level){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, level->texture.memory);

	int x = WINDOW_WIDTH/2;
	int y = WINDOW_HEIGHT/2;

	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(-x,  y); 
		glTexCoord2f(1, 0); glVertex2f( x,  y); 
		glTexCoord2f(1, 1); glVertex2f( x, -y); 
		glTexCoord2f(0, 1); glVertex2f(-x, -y);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void levelRender(Level *level){
	int i;
	backgroundRender(level);
	for(i=0; i<level->width*level->height; i++){
		if(level->bricks[i].broken == 0){
			drawBrick(&level->bricks[i]);
		}
		bonusRender(&level->bricks[i].bonus, level->bricks[i].broken);
	}
}

