#include "Renderer.h"


void Renderer::InitRenderer()
{
    Image image = LoadImage("assets/sprites/player/Player.png");
    playerSpritesheet = LoadTextureFromImage(image);
}

void Renderer::DrawSprite()
{
    Rectangle source = { 0, 0, 16, 16 };
    Rectangle dest{ 0, 0, 64, 64 };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(playerSpritesheet, source, dest, origin, 0, WHITE);

    //DrawTexture(playerSpritesheet, 20, 20, WHITE);
}
