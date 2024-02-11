#version 410 core

layout (location = 0) in uint vertex_data;

uniform vec2 chunk_pos;
uniform mat4 mvp;

out vec3 tex_coord;
out float light;

vec2 tex_coords[4] = vec2[4](
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f),
    vec2(0.0f, 1.0f)
);

void main() {
    // unpack all of our data
    float x = float(vertex_data & 0x1fu);
    float y = float((vertex_data & 0x3e0u) >> 5u);
    float z = float((vertex_data & 0x7c00u) >> 10u);
    float tex = float((vertex_data & 0x7ff8000u) >> 15u);
    uint index = (vertex_data & 0xC0000000u) >> 30u;

    x += chunk_pos.x;
    z += chunk_pos.y;

    gl_Position = mvp * vec4(x, y, z, 1.0);

    tex_coord = vec3(tex_coords[index], tex);
    light = float((vertex_data & 0x38000000u) >> 27u) / 5.0;
}
