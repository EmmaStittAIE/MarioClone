#version 330 core

in vec3 vertexPos;

in vec4 colourIn;
out vec4 fragColour;

void main()
{
	gl_Position = vec4(vertexPos,1.0);
    fragColour = colourIn;
}