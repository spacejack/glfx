#ifndef GLFX_TEXTURE_HPP
#define GLFX_TEXTURE_HPP

#include <string>
#include <GL/glew.h>

namespace GLFX {

class Texture {
public:
	Texture(const char* filename);
	~Texture();
	GLuint id;
	int width;
	int height;
};

}

#endif
