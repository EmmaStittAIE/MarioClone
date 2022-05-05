#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "SDL.h"
#include "GameObject.h"
#include "GL/glew.h"

class Renderer
{
public:
    Renderer(GameObject& go);
    void Render(SDL_Window* window);

private:
    // vars
    GLuint triangleSettings;
    GLuint triangleBuffer;
    GLuint colourBuffer;
    GLuint shaderProg;
    GLuint vertShader;
    GLuint fragShader;
    GLuint elementBuffer;

    GameObject& object;

    // functions
    GLuint LoadShader(std::string fileLocation, GLenum shaderType);
    void CheckLinkSuccess(GLuint& shaderProgram);
};