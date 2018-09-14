#include "texture.hpp"
#include <stdexcept>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

using namespace std;
using namespace GLFX;

Texture::Texture (const char* filename) {
	SDL_Surface* image = nullptr;

	image = IMG_Load(filename);
	if (image == nullptr) {
		throw runtime_error(string("Texture::create failed to load image: ") + SDL_GetError());
	}

	width = image->w;
	height = image->h;

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA, image->w, image->h, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, image->pixels
	);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	SDL_FreeSurface(image);
}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}
