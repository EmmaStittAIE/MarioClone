#include "Game.h"

// timekeeping code courtesy of https://stackoverflow.com/a/59446610

Game::Game()
{
    for (int i = 0; i < maxNumOfNodes; i++)
    {
        nodes[i] = nullptr;
    }

    (new Hitbox(this, { 0.0f, 800.0f, 600.0f, 1000.0f }))->SetDebugColour({ 0, 255, 0, 120 });
    (new Hitbox(this, { 610.0f, 600.0f, 700.0f, 1000.0f }))->SetDebugColour({ 0, 255, 0, 120 });
    new Entity(this, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    /*new Entity(this, nullptr, &spritesheets.playerSpritesheet, {0, 0, 64, 64});
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });
    new Entity(this, nullptr, &spritesheets.playerSpritesheet, { 0, 0, 64, 64 });*/
}

void Game::InitGame()
{
    spritesheets.InitSpritesheets();
    
    SetTargetFPS(60);
}

void Game::Update()
{
    frameTime = GetFrameTime();
    if (frameTime > 0.25) { frameTime = 0.25; }

    accumulator += frameTime;

    while (accumulator >= dt)
    {
        // do stuff here
        for (int i = 0; i < numOfNodes; i++)
        {
            nodes[i]->PUpdate(dt);
        }
        Collisions();
        // end of stuff

        t += dt;
        accumulator -= dt;
    }
}

void Game::Draw()
{
    for (int i = 0; i < numOfNodes; i++)
    {
        nodes[i]->RUpdate();
    }

    BeginDrawing();
    ClearBackground(BLUE);
    
    DrawText(std::to_string(GetFPS()).c_str(), 10, 10, 14, RED);

    // draw all nodes
    for (int i = 0; i < numOfNodes; i++)
    {
        nodes[i]->DrawNode();
    }

    EndDrawing();
}

void Game::Collisions()
{
    // we don't want all nodes to be in the collision step, because, aside from being inefficient, things would break when checking nodes that
    // don't have hitboxes, such as sprites.
    // since hitboxes are aware of their parents, so to speak, we can just compare all of the hitboxes, and if two collide, we tell their parents
    // that a collision has occurred, and they can figure out the rest from there.
    Hitbox** hitboxes = {};
    int numOfHitboxes = 0;

    for (int i = 0; i < numOfNodes; i++)
    {
        GetHitboxes(nodes[i], hitboxes, numOfHitboxes);
    }

    // loop doesn't run until there are at least two hitboxes present - nothing to collide if there's only one, after all
    for (int i = 0; i < numOfHitboxes - 1; i++)
    {
        for (int j = i + 1; j < numOfHitboxes; j++)
        {
            if(hitboxes[i]->CheckCollision(*hitboxes[j]))
            {
                if (hitboxes[i]->GetParent() != nullptr) { hitboxes[i]->GetParent()->HandleCollision(*hitboxes[i], *hitboxes[j]); }
                if (hitboxes[j]->GetParent() != nullptr) { hitboxes[j]->GetParent()->HandleCollision(*hitboxes[j], *hitboxes[i]); }
            }
        }
    }

    delete[] hitboxes;
}

void Game::EndGame()
{
}

void Game::GetHitboxes(Node* node, Hitbox**& hitboxesOut, int& numOfHitboxesOut)
{
    Hitbox** hitboxesTemp = new Hitbox * [numOfHitboxesOut + 1] {};
    for (int i = 0; i < numOfHitboxesOut; i++)
    {
        hitboxesTemp[i] = hitboxesOut[i];
    }

    // dynamic_cast returns a nullptr if it couldn't convert to our desired type - in practise, this means that anything that returns nullptr
    // isn't a hitbox, and thus we skip it and move on to the next
    hitboxesTemp[numOfHitboxesOut] = dynamic_cast<Hitbox*>(node);
    if (hitboxesTemp[numOfHitboxesOut] != nullptr) { numOfHitboxesOut++; }

    for (int i = 0; i < node->GetNumOfChildren(); i++)
    {
        GetHitboxes(node->GetChildren()[i], hitboxesTemp, numOfHitboxesOut);
    }

    hitboxesOut = new Hitbox * [numOfHitboxesOut]{};
    for (int i = 0; i < numOfHitboxesOut; i++)
    {
        hitboxesOut[i] = hitboxesTemp[i];
    }
    delete[] hitboxesTemp;
}

bool Game::AddNode(Node* node)
{
    if (node->IsInitialised())
    {
        std::cout << "Failed to add node - node already exists" << std::endl;
        return false;
    }

    for (int i = 0; i < maxNumOfNodes; i++)
    {
        if (nodes[i] == nullptr)
        {
            nodes[i] = node;
            node->InitNode(i);
            numOfNodes++;

            return true;
        }
    }

    std::cout << "Failed to add node - array too small" << std::endl;
    return false;
}

void Game::DeleteNode(int index)
{
    delete nodes[index];
    nodes[index] = nullptr;

    numOfNodes--;
}

void Game::ClearNodes()
{
    for (int i = 0; i < numOfNodes; i++)
    {
        delete nodes[i];
        nodes[i] = nullptr;
    }
    numOfNodes = 0;
}

Game::~Game()
{
    delete[] nodes;
}
