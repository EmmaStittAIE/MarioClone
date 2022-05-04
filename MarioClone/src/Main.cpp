#include "Main.h"

int main()
{
    SDL_Window* mainWin;
    GLHandler::Init(mainWin);

    // colour floats
    float rCounter = 0;
    float gCounter = 0;
    float bCounter = 0;
    float rVelocity = 0.01;
    float gVelocity = 0.01;
    float bVelocity = 0.01;

    // time variables
    const double dt = 6;
    double accumulatedTime = 0;
    double lastTime = SDL_GetTicks();
    double currentTime;

    // set up our event handler
    SDL_Event event;
    while (1)
    {
        currentTime = SDL_GetTicks();
        accumulatedTime += currentTime - lastTime;
        lastTime = currentTime;

        // loops through all pending events
        while (SDL_PollEvent(&event)) {}

        while (accumulatedTime > dt)
        {
            // Update(dt)

            rCounter += rVelocity;
            gCounter += gVelocity;
            bCounter += bVelocity;
            if (rCounter > 1 || rCounter < 0) { rVelocity *= -1; }
            if (gCounter > 1 || gCounter < 0) { gVelocity *= -1; }
            if (bCounter > 1 || bCounter < 0) { bVelocity *= -1; }

            accumulatedTime -= dt;
        }

        // RENDERING
        glClearColor(rCounter, gCounter, bCounter, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();

        // swap draw buffer with view buffer
        SDL_GL_SwapWindow(mainWin);
    }

    GLHandler::Destroy(mainWin);
    return 0;
}