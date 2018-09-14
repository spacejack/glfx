#ifndef GLFX_PROGRAM_HPP
#define GLFX_PROGRAM_HPP

#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>

namespace GLFX {

class Program {
public:
	Program(
		GLuint vert, GLuint frag,
		const std::vector<const char*> attribs,
		const std::vector<const char*> uniforms
	);
	~Program();
	const GLuint id;
	std::map<std::string, GLuint> attribLocations;
	std::map<std::string, GLuint> uniformLocations;
};

}

#endif
