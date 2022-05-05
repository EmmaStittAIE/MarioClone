#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "GL/glew.h"

class Renderer
{
public:
    Renderer(GameObject& go);
    void Render(SDL_Window* window);

private:
    GameObject& object;
};