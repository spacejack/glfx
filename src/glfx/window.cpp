#include <stdexcept>
#include "window.hpp"

using namespace std;
using namespace GLFX;

void Window::init (const char* title, const Window::Options &options) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw runtime_error(string("Failed to init SDL: ") + SDL_GetError());
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	if (options.doubleBuffer) {
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		printf("Set double buffering\n");
	} else if (options.singleBuffer) {
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 0);
		printf("Set single buffering\n");
	}

	x = SDL_WINDOWPOS_UNDEFINED; y = SDL_WINDOWPOS_UNDEFINED;
	width = options.width; height = options.height;
	auto flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

	if (options.fullscreen) {
		if (options.width < 1 || options.height < 1) {
			SDL_DisplayMode dm;
			if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
				throw runtime_error(string("Failed to get display mode: ") + SDL_GetError());
			}
			width = dm.w; height = dm.h;
		}
		x = 0; y = 0;
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	}

	printf("%s size: %d x %d\n",
		options.fullscreen ? "Fullscreen" : "Windowed", width, height
	);

	window = SDL_CreateWindow(title, x, y, width, height, flags);
	if (window == nullptr) {
		throw runtime_error(string("Failed to create window: ") + SDL_GetError());
	}

	SDL_GetWindowPosition(window, &x, &y);

	printf("Window position: %d, %d\n", x, y);

	context = SDL_GL_CreateContext(window);
	if (context == nullptr) {
		throw runtime_error(string("Failed to create GL context: ") + SDL_GetError());
	}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		throw runtime_error(string("Error initializing GLEW")); // + glewGetErrorString(glewError)
	}

	// Try to use vsync
	if (SDL_GL_SetSwapInterval(1) < 0) {
		fprintf(stderr, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
	}
}

Window::Window (const char* title, const Window::Options& options) {
	init (title, options);
}

Window::Window (const char* title) {
	Options options;
	options.width = 0;
	options.height = 0;
	options.fullscreen = true;
	init (title, options);
}

Window::~Window() {
	SDL_GL_DeleteContext(context);
	context = nullptr;
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void Window::setClearColor (GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glClearColor(r, g, b, a);
}

void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::flip() {
	SDL_GL_SwapWindow(window);
}
