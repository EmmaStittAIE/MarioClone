#include "Renderer.h"


void Renderer::InitRenderer()
{
    Image image = LoadImage("assets/sprites/player/Player.png");
    playerSpritesheet = LoadTextureFromImage(image);
    playerSprite.SetSpritesheet(&playerSpritesheet);
}

void Renderer::DrawSprite()
{
    playerSprite.DrawSprite();
}
