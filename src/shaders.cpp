#include "shaders.hpp"

namespace Shaders {

extern const char tex_vert[] = R"(
precision highp float;

attribute vec2 aPosition;
attribute vec2 aUv;

uniform vec2 uViewport;

varying vec2 vUv;

void main(void) {
    vUv = aUv;
    gl_Position = vec4(
		aPosition.x / uViewport.x, aPosition.y / uViewport.y, 0.5, 1.0
	);
}
)";

extern const char tex_frag[] = R"(
precision highp float;

varying vec2 vUv;

uniform sampler2D uTexture;

void main(void) {
    vec4 color = texture2D(uTexture, vec2(vUv.s, vUv.t));
    gl_FragColor = color;
}
)";

}
