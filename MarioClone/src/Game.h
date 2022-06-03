#pragma once

// timekeeping code courtesy of https://stackoverflow.com/a/59446610

#include <string>
#include <chrono>
#include <mutex>
#include <vector>

#include <raylib.h>

#include "Spritesheets.h"
#include "Entity.h"
#include "Node.h"

class Game
{
public:
    Game();
    void InitGame();
    void Update();
    void Draw();
    void Collisions();
    void EndGame();

    void GetHitboxes(Node* node, Hitbox**& hitboxesOut, int& numOfHitboxesOut);

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
    double accumulator = 0;
    double frameTime = 0;
    double alpha;

    double t = 0.0;
    const double dt = 1.0/60.0;
};

