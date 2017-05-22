#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <GL/gl.h>
#include <GL/glu.h>

typedef struct Texture{
	char folder[100];
	char name[100];
	GLuint memory;
	SDL_Surface *img;
}Texture;

Texture newTexture(char *folder, char *name);

void loadTexture(Texture *texture);

GLenum chosseFormat(Texture *texture);

#endif