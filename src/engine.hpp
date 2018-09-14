#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>
#include "glfx/window.hpp"
#include "glfx/sprite.hpp"
#include "glfx/scene.hpp"
#include "resources.hpp"

class Engine {
public:
	Engine(GLFX::Window& window, Resources& resources);
	~Engine();
	void doFrame();
protected:
	GLFX::Window& window;
	GLFX::Scene scene;
	Uint32 prevT = 0;
	Resources& resources;
	std::vector<std::shared_ptr<GLFX::Sprite>> sprites;
	void update(Uint32 dt);
	void render();
};

#endif
