#include <math.h>
#include <algorithm>
#include <stdexcept>
#include "quadbatch.hpp"

using namespace std;
using namespace glm;
using namespace GLFX;

/** Rotate v by r radians */
static vec2 rotate (vec2 v, float r) {
	float c = cos(r), s = sin(r);
	return vec2{
		v.x * c - v.y * s,
		v.x * s + v.y * c
	};
}

/** Uses pre-computed cos & sin values of rotation angle */
static vec2 rotate (vec2 v, float c, float s) {
	return vec2{
		v.x * c - v.y * s,
		v.x * s + v.y * c
	};
}

QuadBatch::QuadBatch (const Program& p, const Texture& t): program(p), texture(t) {
	glGenBuffers(1, &vboPosition);
	glGenBuffers(1, &vboUv);
	glGenBuffers(1, &vboIndex);
	alocPosition = program.attribLocations.at("aPosition");
	alocUv = program.attribLocations.at("aUv");
	ulocViewport = program.uniformLocations.at("uViewport");
	ulocTexture = program.uniformLocations.at("uTexture");
}

QuadBatch::~QuadBatch() {
	glDeleteBuffers(1, &vboIndex);
	glDeleteBuffers(1, &vboUv);
	glDeleteBuffers(1, &vboPosition);
}

/**
 * Hepler function that (re)fills buffers when quad batch size changes.
 * TODO: Patch buffer more optimally?
 */
void QuadBatch::fillBuffers() {
	glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
	glBufferData(GL_ARRAY_BUFFER,
		position.size() * sizeof(GLfloat), position.data(), GL_STATIC_DRAW
	);

	glBindBuffer(GL_ARRAY_BUFFER, vboUv);
	glBufferData(GL_ARRAY_BUFFER,
		uv.size() * sizeof(GLfloat), uv.data(), GL_STATIC_DRAW
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		index.size() * sizeof(GLushort), index.data(), GL_STATIC_DRAW
	);
}

/**
 * Add a quad to the batch to be drawn
 */
int QuadBatch::add (const Quad& quad) {
	GLushort offset = position.size() / 2;
	position.insert(position.end(), std::begin(quad.position), std::end(quad.position));
	uv.insert(uv.end(), std::begin(quad.uv), std::end(quad.uv));
	for (auto i = 0; i < 6; ++i) {
		index.push_back(offset + quad.index[i]);
	}
	fillBuffers();
	return position.size() / 8;
}

/**
 * Remove a quad from the batch
 */
int QuadBatch::removeAt (int i) {
	// Splice out the verticies
	auto i0 = i * 8;
	auto i1 = (i + 1) * 8;
	position.erase(position.begin() + i0, position.begin() + i1);
	uv.erase(uv.begin() + i0, uv.begin() + i1);
	// Index offsets increment regularly so just remove from the end
	index.erase(index.end() - 6, index.end());
	fillBuffers();
	return position.size() / 8;
}

void QuadBatch::renderSprite (const Sprite* s, int i) {
	auto& sp = s->position;
	auto qp = s->quad.position;
	int o = i * 8;
	for (auto j = 0; j < 8; j += 2) {
		// scale, rotate, translate
		auto p = rotate(vec2(qp[j], qp[j + 1]) * s->scale, s->rotation) + sp;
		position[o + j + 0] = p.x;
		position[o + j + 1] = p.y;
	}
}

void QuadBatch::renderSprites() {
	for (auto i = 0; i < sprites.size(); ++i) {
		renderSprite(sprites[i].get(), i);
	}

	// Update the VBOs
	glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
	glBufferData(GL_ARRAY_BUFFER,
		position.size() * sizeof(GLfloat), position.data(), GL_STATIC_DRAW
	);
}

int QuadBatch::add (shared_ptr<const Sprite> sprite) {
	auto i = std::find(sprites.begin(), sprites.end(), sprite);
	if (i != sprites.end()) {
		throw runtime_error("QuadBatch::add - Sprite was already added");
	}
	add(sprite->quad);
	sprites.push_back(sprite);
	return sprites.size();
}

int QuadBatch::remove (shared_ptr<const Sprite> sprite) {
	auto i = std::find(sprites.begin(), sprites.end(), sprite);
	if (i == sprites.end()) {
		throw runtime_error("QuadBatch::remove - Sprite not found");
	}
	removeAt(i - sprites.begin());
	sprites.erase(i);
	return sprites.size();
}

/**
 * Render the batch
 */
void QuadBatch::render (vec2& viewport) {
	if (index.size() < 1) {
		return;
	}

	renderSprites();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(program.id);

	glUniform1i(ulocTexture, 0);
	glUniform2f(ulocViewport, viewport[0], viewport[1]);

	glBindBuffer(GL_ARRAY_BUFFER, vboPosition);
	glVertexAttribPointer(alocPosition, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboUv);
	glVertexAttribPointer(alocUv, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndex);

	glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_SHORT, 0);
}
