#include <stdio.h>
#include "sprite.hpp"

using namespace GLFX;

Sprite::Sprite(const Quad &q): quad(q) {
	position = {0.0f, 0.0f};
	scale = {1.0f, 1.0f};
	rotation = 0.0f;
}

Sprite::~Sprite() {
	//printf("Sprite deleted\n");
}
