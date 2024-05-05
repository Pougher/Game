#version 410 core

out vec4 FragColor;
in vec2 texcoord;

uniform sampler2DArray depthmap;

void main() {
    vec4 v = texture(depthmap, vec3(texcoord, 0));
    FragColor = v;
}
