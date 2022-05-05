#include "Input.h"

Input::Input(GameObject& go)
    :object(go)
{
    keyboardState = SDL_GetKeyboardState(&numKeys);
}

void Input::HandleInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {}

    if (keyboardState[SDL_SCANCODE_R])
    {
        if (keyboardState[SDL_SCANCODE_LCTRL]) { object.backgroundColour[0] -= 0.01; }
        else { object.backgroundColour[0] += 0.01; }
    }

    if (keyboardState[SDL_SCANCODE_G])
    {
        if (keyboardState[SDL_SCANCODE_LCTRL]) { object.backgroundColour[1] -= 0.01; }
        else { object.backgroundColour[1] += 0.01; }
    }

    if (keyboardState[SDL_SCANCODE_B])
    {
        if (keyboardState[SDL_SCANCODE_LCTRL]) { object.backgroundColour[2] -= 0.01; }
        else { object.backgroundColour[2] += 0.01; }
    }

    if (keyboardState[SDL_SCANCODE_W])
    {
        if (keyboardState[SDL_SCANCODE_LCTRL])
        {
            object.backgroundColour[0] -= 0.01;
            object.backgroundColour[1] -= 0.01;
            object.backgroundColour[2] -= 0.01;
        }
        else
        {
            object.backgroundColour[0] += 0.01;
            object.backgroundColour[1] += 0.01;
            object.backgroundColour[2] += 0.01;
        }
    }

    if (keyboardState[SDL_SCANCODE_SPACE])
    {
        object.backgroundColour[0] = 0;
        object.backgroundColour[1] = 0;
        object.backgroundColour[2] = 0;
    }

    if (object.backgroundColour[0] > 1) { object.backgroundColour[0] = 1; }
    if (object.backgroundColour[1] > 1) { object.backgroundColour[1] = 1; }
    if (object.backgroundColour[2] > 1) { object.backgroundColour[2] = 1; }

    if (object.backgroundColour[0] < 0) { object.backgroundColour[0] = 0; }
    if (object.backgroundColour[1] < 0) { object.backgroundColour[1] = 0; }
    if (object.backgroundColour[2] < 0) { object.backgroundColour[2] = 0; }
}
