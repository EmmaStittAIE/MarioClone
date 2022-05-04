#include "Main.h"

int main()
{
    SDL_Window* mainWin;
    Init(mainWin);

    // set up our event handler and game loop
    SDL_Event event;
    while (1)
    {
        // loops through all pending events
        while (SDL_PollEvent(&event)) { }

        // swap draw buffer with view buffer
        SDL_GL_SwapWindow(mainWin);
    }
    return 0;
}