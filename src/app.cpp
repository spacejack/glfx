#include "glfx/texture.hpp"
#include "glfx/shader.hpp"
#include "glfx/program.hpp"
#include "app.hpp"
#include "config.hpp"
#include "resources.hpp"
#include "engine.hpp"

using namespace std;
using namespace GLFX;

void App::run() {
	SDL_Event e;
	auto quit = false;
	Resources resources(Config::basedir);
	Engine engine(window, resources);

	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN) {
				auto key = e.key.keysym.sym;
				if (key == SDLK_q || key == SDLK_ESCAPE) {
					quit = true;
				} else {
					printf("key: %d\n", (int)key);
				}
			}
		}

		if (quit) {
			break;
		}
		engine.doFrame();
	}
}
