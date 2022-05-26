#pragma once

#include <iostream>

#include "raylib.h"

class Renderer
{
public:
    void InitRenderer();
    void DrawSprite();

private:
    Texture playerSpritesheet;
    Texture enemySpritesheet;
    Texture itemSpritesheet;
    Texture terrainSpritesheet;
};

