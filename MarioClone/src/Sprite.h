#pragma once

#include "raylib.h"

struct Animation
{
    char currentFrame;
    char numOfFrames;
    char framerate;
    bool loop;
    bool mustFinish;
    Rectangle frames[10];
};

class Sprite
{
public:
    Sprite();
    void SetSpritesheet(Texture* spritesheetPointer);
    void DrawSprite();

private:
    Texture* spritesheet;

    Animation* currentAnim;
    Animation animIdle = { 0, 1, 0, 0, 0, {{0, 0, 16, 16}} };
    Animation animWalk = { 0, 3, 10, 1, 0, {{16, 0, 16, 16}, {32, 0, 16, 16}, {48, 0, 16, 16}} };

    int framesPassed = 0;
};

