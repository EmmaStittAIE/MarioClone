#pragma once

#include <GL/glew.h>

#define SDL_MAIN_HANDLED
#include "SDL.h"

// Creates a window, initialises GL and GLEW
bool Init(SDL_Window*& window);

// Call this before creating a GL context
void SetGLAttributes(int glMajorVersion, int glMinorVersion, int useDoubleBuffering);