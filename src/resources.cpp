#include "resources.hpp"
#include "glfx/shader.hpp"
#include "shaders.hpp"

using namespace std;
using namespace GLFX;

Resources::Resources (string path):
	program(
		Shader::create(GL_VERTEX_SHADER, Shaders::tex_vert),
		Shader::create(GL_FRAGMENT_SHADER, Shaders::tex_frag),
		{"aPosition", "aUv"}, {"uTexture", "uViewport"}
	),
	texture(Texture((path + "/tex/ship.png").c_str()))
{
	printf("Initialized resources\n");
}

Resources::~Resources() {}
