#ifndef GLFX_QUAD_HPP
#define GLFX_QUAD_HPP

#include <GL/glew.h>

namespace GLFX {

struct Quad {
    GLfloat position[8] = {-1.0, -1.0, 1.0, -1.0, 1.0, 1.0, -1.0, 1.0};
    GLfloat uv[8] = {0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0};
    GLshort index[6] = {0, 1, 2, 2, 3, 0};
};

}

#endif
