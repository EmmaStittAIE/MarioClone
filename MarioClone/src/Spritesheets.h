#pragma once

#include <iostream>

#include <raylib.h>
#include "Sprite.h"

class Spritesheets
{
public:
    Texture playerSpritesheet;
    Texture enemySpritesheet;
    Texture itemSpritesheet;
    Texture terrainSpritesheet;

    void InitSpritesheets();
};

