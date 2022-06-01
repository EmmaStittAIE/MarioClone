#include "Game.h"

Game::Game()
    : entity{ &spritesheets.playerSpritesheet, {0, 0, 64, 64} },
      hitbox{ {0.0f, 800.0f, 600.0f, 1000.0f} },
      hitbox2{ {610.0f, 600.0f, 700.0f, 1000.0f} }
{}

void Game::InitGame()
{
    spritesheets.InitSpritesheets();

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
    Collisions();

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

    DrawRectangle(entity.hitbox.GetLeft(), entity.hitbox.GetTop(), entity.hitbox.GetWidth(), entity.hitbox.GetHeight(), { 255, 0, 0, 100 });
    DrawRectangle(hitbox.GetLeft(), hitbox.GetTop(), hitbox.GetWidth(), hitbox.GetHeight(), { 0, 255, 0, 100 });
    DrawRectangle(hitbox2.GetLeft(), hitbox2.GetTop(), hitbox2.GetWidth(), hitbox2.GetHeight(), {0, 255, 0, 100});

    EndDrawing();
}

void Game::Collisions()
{
    Sides sidesHit = static_cast<Sides>(0);
    if (entity.hitbox.CheckCollision(hitbox, &sidesHit))
    {
        entity.HandleCollision(hitbox, sidesHit);
    }
    if (entity.hitbox.CheckCollision(hitbox2, &sidesHit))
    {
        entity.HandleCollision(hitbox2, sidesHit);
    }
}

void Game::EndGame()
{
}
