#pragma once

#include <GL/glew.h>

#define SDL_MAIN_HANDLED
#include "SDL.h"

class GLHandler
{
public:
    // Creates a window, initialises GL and GLEW
    static bool Init(SDL_Window*& window);

    // Call at end of program
    static void Destroy(SDL_Window*& window);

private:
    GLHandler() {}

    // Call this before creating a GL context
    static void SetGLAttributes(int glMajorVersion, int glMinorVersion, int useDoubleBuffering);
};


