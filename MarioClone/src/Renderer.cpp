#include "Renderer.h"

Renderer::Renderer(GameObject& go)
    :object(go) { }

void Renderer::Render(SDL_Window* win)
{
    glClearColor(object.backgroundColour[0], object.backgroundColour[1], object.backgroundColour[2], object.backgroundColour[3]);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    // swap draw buffer with view buffer
    SDL_GL_SwapWindow(win);
}