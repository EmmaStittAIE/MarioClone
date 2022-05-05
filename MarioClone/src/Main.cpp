#include "Main.h"

int main()
{
    SDL_Window* mainWin;
    GLHandler::Init(mainWin);

    GameObject object;
    Input input(object);
    Renderer renderer(object);

    // time variables
    const double dt = 6;
    double accumulatedTime = 0;
    double lastTime = SDL_GetTicks();
    double currentTime;

    // set up our event handler
    while (1)
    {
        currentTime = SDL_GetTicks();
        accumulatedTime += currentTime - lastTime;
        lastTime = currentTime;

        // loops through all events and input
        input.HandleInput();

        while (accumulatedTime > dt)
        {
            // Update(dt)
            accumulatedTime -= dt;
        }

        // RENDERING
        renderer.Render(mainWin);
    }

    GLHandler::Destroy(mainWin);
    return 0;
}