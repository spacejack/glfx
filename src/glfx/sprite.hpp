#ifndef GLFX_SPRITE_HPP
#define GLFX_SPRITE_HPP

#include "glm/vec2.hpp"
#include "quad.hpp"

namespace GLFX {

class Sprite {
public:
	Sprite(const Quad& quad);
	~Sprite();
	const Quad& quad;
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;
};

}

#endif
