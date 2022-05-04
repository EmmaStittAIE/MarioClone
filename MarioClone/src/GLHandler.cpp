#include <iostream>

#include "GLHandler.h"

bool GLHandler::Init(SDL_Window*& window)
{
    SDL_Init(SDL_INIT_EVERYTHING); // may be worth looking into SDL_Init a bit further in future, to see if theres a reason to init certain things in sequence rather than all together
    SetGLAttributes(4, 6, 1);
    window = SDL_CreateWindow("Hi hi~", 500, 200, 800, 600, SDL_WINDOW_OPENGL); // window tags also seem interesting to look into
    // SDL_CreateWindow returns null if something goes wrong, so if the window is null we know something went wrong and have to abort
    // we return a false bool value here to tell the user that something failed and initialisation did not complete successfully
    if (window == NULL)
    {
        std::cout << "Window failed to initialise at startup\n";
        return false;
    }
    // should research what an OpenGL context is, but this function creates one for window
    SDL_GL_CreateContext(window);

    // try to set the swap interval (how often the draw buffer and display buffer are swapped) to adaptive vsync
    if (SDL_GL_SetSwapInterval(-1) == -1)
    {
        // if trying that returns a -1, then it means adaptive vsync is unsupported. in this case, we should just set it to regular vsync
        SDL_GL_SetSwapInterval(1);
    }

    glewExperimental = GL_TRUE; // allows us to use all GLEW functions
    glewInit();

    return true;
}

void GLHandler::Destroy(SDL_Window*& window)
{
    SDL_GL_DeleteContext(window);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void GLHandler::SetGLAttributes(int glMajorVersion, int glMinorVersion, int useDoubleBuffering)
{
    // disable deprecated functions
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Set OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glMajorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glMinorVersion);

    // set doublebuffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, useDoubleBuffering);
}
