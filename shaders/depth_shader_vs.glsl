#version 410 core

layout (location = 0) in uvec2 vertex_data;

uniform vec2 chunk_pos;
uniform mat4 light_space_matrix;

void main() {
    uint low = vertex_data.x;

    float x = float(low & 0x3fu) + chunk_pos.x;
    float z = float((low & 0xfc0u) >> 6u) + chunk_pos.y;
    float y = float(vertex_data.y & 0x3ffu);

    gl_Position = light_space_matrix * vec4(x, y, z, 1.0);
}
