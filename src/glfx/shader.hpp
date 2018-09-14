#ifndef GLFX_SHADER_HPP
#define GLFX_SHADER_CPP

#include <GL/glew.h>

namespace GLFX {

namespace Shader {

GLuint create (GLenum type, const char *src);
void destroy (GLuint shader);

};

}

#endif
