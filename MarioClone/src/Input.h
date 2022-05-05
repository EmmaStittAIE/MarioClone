#pragma once

#include "SDL.h"
#include "GameObject.h"

class Input
{
public:
    void HandleInput();
    Input(GameObject& go);

private:
    GameObject& object;
    const Uint8* keyboardState;
    int numKeys;
};

