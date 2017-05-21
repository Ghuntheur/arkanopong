#include "texture.h"

Texture newTexture(char *folder, char *name){
	Texture t;

	t.folder = strcpy(t.folder, folder);
	t.name   = strcpy(t.name, name);

	/*loadTexture(&t);*/

	return t;
}

void loadTexture(Texture *texture){
	/*strcpy(texture->path, strcat(texture->folder, strcat(texture->name, "/")));*/
	printf("%s\n", texture->path);
}