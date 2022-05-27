#include "Spritesheets.h"

void Spritesheets::InitSpritesheets()
{
    Image image = LoadImage("assets/sprites/player/Player.png");
    playerSpritesheet = LoadTextureFromImage(image);
}
