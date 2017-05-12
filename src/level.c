#include "level.h"

int buildLevel(Level *level){
	FILE *file = initLevel(level);
	if(file == NULL) return EXIT_FAILURE;
	if(allocBricksMemory(level) == EXIT_FAILURE) return EXIT_FAILURE;
	if(createBricks(level, file) == EXIT_FAILURE) return EXIT_FAILURE;
	
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

int createBricks(Level *level, FILE *file){
	int i, j, num, count = 0;
	for(j=0; j<level->height; j++){
		for(i=0; i<level->width; i++){
			fscanf(file, "%d ", &num);
			level->bricks[count] = newBrick(num, level->width, level->height, i, j);
			count++;
		}
	}

	fclose(file);	
	return EXIT_SUCCESS;
}

void levelRender(Level *level){
	int i;
	for(i=0; i<level->width*level->height; i++){
		if(level->bricks[i].broken == 0){
			drawBrick(&level->bricks[i]);
		}		
	}
}