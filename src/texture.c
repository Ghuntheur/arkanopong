#include "texture.h"

Texture newTexture(char *folder, char *name){
	Texture t;

	strcpy(t.folder, folder);
	strcpy(t.name, name);

	loadTexture(&t);

	return t;
}

void loadTexture(Texture *texture){

	texture->img = IMG_Load(strcat(texture->folder, texture->name));

	if(texture->img == NULL){
		printf("Erreur lors du chargement des textures\n");
		return;
	}

	glGenTextures(1, &texture->memory);
	glBindTexture(GL_TEXTURE_2D, texture->memory);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		GL_RGB, 
		texture->img->w, 
		texture->img->h, 
		0, 
		chosseFormat(texture), 
		GL_UNSIGNED_BYTE, 
		texture->img->pixels
	);

	SDL_FreeSurface(texture->img);
	glBindTexture(GL_TEXTURE_2D, texture->memory);
}

GLenum chosseFormat(Texture *texture){
	GLenum format;
	switch(texture->img->format->BytesPerPixel){
	case 1:
		format = GL_RED;
		break;

	case 3:
		format = GL_RGB;
		break;
	
	case 4:
		format = GL_RGBA;
		break;
	
	default:
		break;
	}
	return format;
}
