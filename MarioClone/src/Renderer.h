#pragma once

#include <iostream>

#include "raylib.h"
#include "Sprite.h"

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

    Sprite playerSprite;
};

