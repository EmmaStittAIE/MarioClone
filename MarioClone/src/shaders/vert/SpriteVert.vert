#version 330 core

layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texScreenCoords>

out vec2 TexScreenCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexScreenCoords = vertex.zw;
    gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
}