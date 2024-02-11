#version 410 core

out vec4 FragColor;

in vec3 tex_coord;
in float light;

uniform sampler2DArray tex;

void main() {
    FragColor = texture(tex, tex_coord) * light;
}
