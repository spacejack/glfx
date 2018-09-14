#include <string>
#include <stdexcept>
#include "shader.hpp"

using namespace std;
using namespace GLFX;

GLuint Shader::create (GLenum type, const char *src) {
	auto shader = glCreateShader(type);
	if (shader == 0) {
		throw runtime_error("Failed to create shader");
	}

	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);
	GLint compiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		GLint infoLen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
		string message = "Error compiling shader";
		if (infoLen > 1) {
			auto infoLog = new char[infoLen + 4];
			glGetShaderInfoLog(shader, infoLen, nullptr, infoLog);
			message += string(":\n") + infoLog;
			delete[] infoLog;
		}
		glDeleteShader(shader);
		throw runtime_error(message);
	}

	return shader;
}

void Shader::destroy (GLuint shader) {
	glDeleteShader(shader);
}
