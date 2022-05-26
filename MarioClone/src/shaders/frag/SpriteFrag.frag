#version 330 core

in vec2 TexScreenCoords;

out vec4 colour;

uniform sampler2D image;
uniform vec3 spriteColour;

void main()
{    
    colour = vec4(spriteColour, 1.0) * texture(image, TexScreenCoords);
}  