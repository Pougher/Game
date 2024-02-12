#version 410 core

layout (location = 0) in uvec2 vertex_data;

uniform vec2 chunk_pos;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

out vec3 tex_coord;
out vec3 light;

vec2 tex_coords[4] = vec2[4](
    vec2(0.0f, 0.0f),
    vec2(1.0f, 0.0f),
    vec2(1.0f, 1.0f),
    vec2(0.0f, 1.0f)
);

void main() {
    // unpack all of our data
    uint low = vertex_data.x;

    float x = float(low & 0x3fu);
    float z = float((low & 0xfc0u) >> 6u);
    float tex = float((low & 0xfff000u) >> 12u);
    uint index = (low & 0xc0000000u) >> 30u;

    // decompress lighting
    uint lighting = (low & 0x3f000000u) >> 24u;
    light = vec3(
        float(lighting & 0x03u) / 4.0f + 0.25f,
        float((lighting & 0x0cu) >> 2u) / 4.0f + 0.25f,
        float((lighting & 0x30u) >> 4u) / 4.0f + 0.25f);

    // y coordinate in another uint
    float y = float(vertex_data.y & 0x3ffu);

    // fix the X and Z positions by offsetting them by the chunk position
    x += chunk_pos.x;
    z += chunk_pos.y;

    gl_Position = projection * view * model * vec4(x, y, z, 1.0);

    tex_coord = vec3(tex_coords[index], tex);
}
