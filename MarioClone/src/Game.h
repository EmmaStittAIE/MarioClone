#pragma once

// timekeeping code courtesy of https://stackoverflow.com/a/59446610

#include <string>
#include <chrono>
#include <mutex>

#include <raylib.h>

#include "Spritesheets.h"
#include "Entity.h"
#include "Node.h"

auto constexpr dt = std::chrono::duration<long long, std::ratio<1, 60>>{ 1 };
using Clock = std::chrono::steady_clock;
using duration = decltype(Clock::duration{} + dt);
using time_point = std::chrono::time_point<Clock, duration>;
using namespace std::literals;

class Game
{
public:
    Game();
    void InitGame();
    void Update();
    void Draw();
    void Collisions();
    void EndGame();

    bool AddNode(Node* node);
    void DeleteNode(int index);
    void DeleteNode(Node* node) { DeleteNode(node->GetIndex()); }
    void ClearNodes();

    ~Game();

private:
    int numOfNodes = 0;
    int maxNumOfNodes = 100;
    Node** nodes = new Node*[maxNumOfNodes]{};
    std::once_flag nodeMemAssigned;

    Spritesheets spritesheets;
    Camera2D camera;

    // timing
    time_point t{};
    time_point currentTime;
    time_point previousTime;
    duration accumulator;
};

