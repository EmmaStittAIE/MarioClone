#pragma once

#include <string>
#include <chrono>

#include "raylib.h"
#include "Spritesheets.h"
#include "Entity.h"

class Game
{
public:
    void InitGame();
    void Update();
    void Draw();
    void EndGame();

private:
    Spritesheets spritesheets;
    Entity entity;
    Camera2D camera;

    // timing
    //std::chrono::steady_clock clock;
    std::clock_t currentTime;
    std::clock_t previousTime;
    float timer = 0;
    float deltaTime = 0;
    int fps = 0;
    int frames = 0;
};

