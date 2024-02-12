#version 410 core

out vec4 FragColor;

in vec3 tex_coord;
in vec3 light;

uniform sampler2DArray tex;

void main() {
    vec4 col = texture(tex, tex_coord);
    FragColor = vec4(col.xyz * light, col.a);
}
