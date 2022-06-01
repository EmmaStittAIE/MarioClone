#pragma once

#include <string>
#include <chrono>

#include "raylib.h"
#include "Spritesheets.h"
#include "Entity.h"

class Game
{
public:
    Game();
    void InitGame();
    void Update();
    void Draw();
    void Collisions();
    void EndGame();

private:
    Spritesheets spritesheets;
    Hitbox hitbox; // remove later
    Hitbox hitbox2; // remove later
    Entity entity; // remove later
    Camera2D camera;

    // timing
    std::clock_t currentTime;
    std::clock_t previousTime;
    float timer = 0;
    float deltaTime = 0;
    int fps = 0;
    int frames = 0;
};

