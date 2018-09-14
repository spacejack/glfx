#include "scene.hpp"

using namespace std;
using namespace GLFX;

Scene::Scene(const Program &p, const Texture &t): quadBatch(p, t) {}

Scene::~Scene() {}

shared_ptr<GLFX::Sprite> Scene::createSprite (const Quad& quad) {
	return shared_ptr<Sprite>(new Sprite(quad));
}

void Scene::render() {
	quadBatch.render(viewport);
}
