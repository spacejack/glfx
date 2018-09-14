#include "engine.hpp"
#include "glfx/sprite.hpp"

using namespace std;
using namespace GLFX;

Engine::Engine (Window& w, Resources& r):
	window(w), resources(r),
	scene(r.program, r.texture)
{
	glViewport(0, 0, window.width, window.height);
	float aspect = (float)window.width / (float)window.height;
	scene.viewport = {aspect * 4.0f, 4.0f};
	glDisable(GL_DEPTH_TEST);
	window.setClearColor(0.1f, 0.2f, 0.3f, 1.0f);

	// Add some Sprites
	for (auto i = 0; i < 32; ++i) {
		auto sprite = scene.createSprite(resources.unitQuad);
		scene.quadBatch.add(sprite);
		sprites.push_back(sprite);
	}

	prevT = SDL_GetTicks();
}

Engine::~Engine() {}

void Engine::doFrame() {
	auto curT = SDL_GetTicks();
	auto dt = curT - prevT;
	if (dt > 0) {
		if (dt > 100) {
			prevT += dt - 100;
			dt = 100;
		}
		update(dt);
		render();
		window.flip();
	}
	prevT = curT;
}

static float detRand (float s) {
	return 0.5f + sin(s * 123456789.0f) / 2.0f;
}

void Engine::update (Uint32 dt) {
	const auto ft = (prevT + dt) / 1000.0f;
	int i = 0, n = sprites.size();
	for (auto& sprite: sprites) {
		auto r = detRand((float)i / n);
		auto t = (ft * (r * 0.5 + 0.5)) + i * 2.0f * M_PI / n;
		r = detRand((float)((i + n / 2) % n) / n);
		auto d = 2.0f + 2.0f * r;
		sprite->position = {cos(t) * d, sin(t) * d};
		sprite->rotation = t;
		auto s = cos(ft) * 0.25f + 0.75f;
		sprite->scale = {s, s};
		++i;
	}
}

void Engine::render() {
	window.clear();
	scene.render();
}
