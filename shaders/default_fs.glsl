#version 410 core
out vec4 FragColor;
in vec2 texcoord;

uniform sampler2DArray tex;

void main()
{
    FragColor = texture(tex, vec3(texcoord, 243));
}
