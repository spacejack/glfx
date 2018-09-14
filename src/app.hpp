#ifndef APP_HPP
#define APP_HPP

#include <vector>
#include "glfx/window.hpp"

class App {
public:
	GLFX::Window& window;
	App(GLFX::Window& w): window(w) {}
	~App() = default;
	void run();
};

#endif
