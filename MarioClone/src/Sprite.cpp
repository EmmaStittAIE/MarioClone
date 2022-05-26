#include "Sprite.h"

Sprite::Sprite()
{
    currentAnim = &animWalk;
}

void Sprite::SetSpritesheet(Texture* spritesheetPointer)
{
    spritesheet = spritesheetPointer;
}

void Sprite::DrawSprite()
{
    framesPassed++;
    if (currentAnim->framerate != 0 && framesPassed >= 60 / currentAnim->framerate)
    {
        currentAnim->currentFrame++;
        if (currentAnim->currentFrame >= currentAnim->numOfFrames) { currentAnim->currentFrame = 0; }

        framesPassed = 0;
    }

    Rectangle source = currentAnim->frames[currentAnim->currentFrame];
    Rectangle dest{ 0, 0, 64, 64 };
    Vector2 origin = { 0, 0 };
    DrawTexturePro(*spritesheet, source, dest, origin, 0, WHITE);
}
