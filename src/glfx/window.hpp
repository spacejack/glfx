#ifndef GLFX_WINDOW_HPP
#define GLFX_WINDOW_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace GLFX {

class Window {
public:
	struct Options {
		bool fullscreen = false;
		bool doubleBuffer = false;
		bool singleBuffer = false;
		int width = 0;
		int height = 0;
	};

	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;
	int x;
	int y;
	int width;
	int height;
	/** Initialize fullscreen */
	Window(const char *title);
	/** Initialize windowed */
	Window(const char *title, const Options& options);
	~Window();
	void setClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void clear();
	void flip();

protected:
	void init(const char *title, const Options& options);
};

}

#endif
