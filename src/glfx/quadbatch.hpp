#ifndef GLFX_QUADBATCH_HPP
#define GLFX_QUADBATCH_HPP

#include <memory>
#include <glm/vec2.hpp>
#include "quad.hpp"
#include "texture.hpp"
#include "program.hpp"
#include "sprite.hpp"

namespace GLFX {

class QuadBatch {
protected:
	void fillBuffers();
	int add(const Quad& quad);
	int removeAt(int index);
	void renderSprite(const Sprite* sprite, int i);
	void renderSprites();
	const Texture &texture;
	const Program &program;
	std::vector<std::shared_ptr<const Sprite>> sprites;
	// Attribute data
	std::vector<GLfloat> position;
	std::vector<GLfloat> uv;
	// Index data
	std::vector<GLushort> index;
	// Vertex Buffer Objects
	GLuint vboPosition;
	GLuint vboUv;
	GLuint vboIndex;
	// Attribute locations
	GLuint alocPosition;
	GLuint alocUv;
	// Uniform locations
	GLuint ulocViewport;
	GLuint ulocTexture;
public:
	QuadBatch(const Program& program, const Texture& texture);
	~QuadBatch();
	int add(std::shared_ptr<const Sprite> sprite);
	int remove(std::shared_ptr<const Sprite> sprite);
	void render(glm::vec2& viewport);
};

}

#endif
