#include "Game.h"

void Game::InitGame()
{
    spritesheets.InitSpritesheets();
    entity.Init(&spritesheets.playerSpritesheet);

    previousTime = std::clock();
    SetTargetFPS(60);
}

void Game::Update()
{
    currentTime = std::clock();
    deltaTime = (currentTime - previousTime) / 1000.0f;
    timer += deltaTime;
    if (timer >= 1.0f)
    {
        fps = frames;
        frames = 0;
        timer -= 1;
    }
    
    // do stuff here
    entity.PUpdate(deltaTime);

    frames++;
    previousTime = currentTime;
}

void Game::Draw()
{
    entity.RUpdate(deltaTime);

    BeginDrawing();
    ClearBackground(BLUE);
    
    DrawText(std::to_string(fps).c_str(), 10, 10, 14, RED);

    //spritesheets.DrawSprite();
    entity.sprite.DrawSprite();

    EndDrawing();
}

void Game::EndGame()
{
}
