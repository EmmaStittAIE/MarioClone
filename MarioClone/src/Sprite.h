#pragma once

#include <algorithm>

#include <raylib.h>

#include "Exceptions.h"
#include "Node.h"

struct Animation
{
    unsigned char currentFrame;
    unsigned char numOfFrames;
    unsigned char framerate;
    bool loop;
    bool mustFinish;
    Rectangle frames[10];
};

struct Palette
{
    Color first;
    Color second;
    Color third;
    Color fourth;
};

class Sprite : public Node
{
public:
    Sprite(Game* gamePointer, class Texture* spritesheetPointer);
    Sprite(Game* gamePointer, class GameObject* parentPointer, class Texture* spritesheetPointer);
    void AdvanceAnimation();
    void Draw() override;

    void SetAnimation(int index) { framesPassed = 0; currentAnim->currentFrame = 0; currentAnim = &animations[index]; currentAnimIndex = index; }
    void SetFacingRight(bool right) { facingRight = right; }

    int GetCurrentAnimIndex() { return currentAnimIndex; }
    bool GetFacingRight() { return facingRight; }

protected:
    void RenderingUpdate() override;

private:
    Texture* spritesheet = nullptr;

    Image colouredImage;
    Texture colouredTexture;

    Animation* currentAnim = nullptr;
    int currentAnimIndex = 0;

    Animation animIdle = { 0, 1, 0, 0, 0, {{0, 0, 16, 16}} };
    Animation animWalk = { 0, 3, 0, 1, 0, {{16, 0, 16, 16}, {32, 0, 16, 16}, {48, 0, 16, 16}} };
    Animation animSkid = { 0, 1, 0, 0, 0, {{64, 0, 16, 16}} };
    Animation animJump = { 0, 1, 0, 0, 0, {{80, 0, 16, 16}} };
    Animation animations[20];
    Palette palettes[10];

    int framesPassed = 0;
    float floatFramerate = 0;

    bool facingRight = true;
};

