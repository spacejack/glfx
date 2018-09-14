#ifndef APP_RESOURCES_HPP
#define APP_RESOURCES_HPP

#include <string>
#include <GL/glew.h>
#include "glfx/quad.hpp"
#include "glfx/texture.hpp"
#include "glfx/program.hpp"

class Resources {
public:
	Resources(std::string path);
	~Resources();
	GLFX::Texture texture;
	GLFX::Program program;
	GLFX::Quad unitQuad;
};

#endif
