#include "Sprite.h"
#include "GameObject.h"
#include "Entity.h"

Sprite::Sprite(Game* gamePointer, Texture* spritesheetPointer)
    : Node(gamePointer)
{
    spritesheet = spritesheetPointer;

    animations[0] = animIdle;
    animations[1] = animWalk;
    animations[2] = animSkid;
    animations[3] = animJump;
    currentAnim = &animations[1];

    palettes[0] = { {0xFF, 0xFF, 0xFF, 0xFF}, {0xAD, 0xAD, 0xAD, 0xFF}, {0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF} };
    palettes[1] = { {0x00, 0x00, 0x00, 0x00}, {0xB5, 0x31, 0x20, 0xFF}, {0xEA, 0x9E, 0x22, 0xFF}, {0x6B, 0x6D, 0x00, 0xFF} };
}

Sprite::Sprite(Game* gamePointer, class GameObject* parentPointer, Texture* spritesheetPointer)
    : Node(gamePointer, parentPointer)
{
    spritesheet = spritesheetPointer;

    animations[0] = animIdle;
    animations[1] = animWalk;
    animations[2] = animSkid;
    animations[3] = animJump;
    currentAnim = &animations[1];

    palettes[0] = { {0xFF, 0xFF, 0xFF, 0xFF}, {0xAD, 0xAD, 0xAD, 0xFF}, {0x66, 0x66, 0x66, 0xFF}, {0x00, 0x00, 0x00, 0xFF} };
    palettes[1] = { {0x00, 0x00, 0x00, 0x00}, {0xB5, 0x31, 0x20, 0xFF}, {0xEA, 0x9E, 0x22, 0xFF}, {0x6B, 0x6D, 0x00, 0xFF} };
}

void Sprite::AdvanceAnimation()
{
    floatFramerate = fabs(((Entity*)parent)->GetVelocity().x) * 2;

    framesPassed++;
    currentAnim->framerate = floatFramerate;
    while (currentAnim->framerate != 0 && framesPassed >= GetFPS() / currentAnim->framerate)
    {
        currentAnim->currentFrame++;
        if (currentAnim->currentFrame >= currentAnim->numOfFrames) { currentAnim->currentFrame = 0; }

        framesPassed -= (currentAnim->framerate < GetFPS()) ? framesPassed : GetFPS();
    }
}

void Sprite::Draw(const double alpha)
{
    if (spritesheet == nullptr) { throw NotInitialisedException(); }

    UnloadImage(colouredImage);
    UnloadTexture(colouredTexture);

    colouredImage = LoadImageFromTexture(*spritesheet);
    ImageColorReplace(&colouredImage, palettes[0].first, palettes[1].first);
    ImageColorReplace(&colouredImage, palettes[0].second, palettes[1].second);
    ImageColorReplace(&colouredImage, palettes[0].third, palettes[1].third);
    ImageColorReplace(&colouredImage, palettes[0].fourth, palettes[1].fourth);
    colouredTexture = LoadTextureFromImage(colouredImage);

    Rectangle sourceRect = currentAnim->frames[currentAnim->currentFrame];
    sourceRect.width *= facingRight ? 1 : -1;
    DrawTexturePro(colouredTexture, sourceRect, { 0, 0, 64, 64 }, -((position * alpha) + (previousPos * (1.0 - alpha))), 0, WHITE);
}

void Sprite::RenderingUpdate()
{
    AdvanceAnimation();
}
