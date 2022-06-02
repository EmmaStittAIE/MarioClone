#pragma once

#include <raylib.h>

class Node
{
public:
    Node(class Game* gamePointer);
    Node(Game* gamePointer, Node* parentPointer);
    void InitNode(int index) { nodeIndex = index; }

    void PUpdate(float delta);
    void RUpdate();

    virtual void HandleCollision(class Hitbox& thisBox, Hitbox& collision) {}

    Node* GetParent() { return parent; }
    virtual Vector2 GetPos() { return position; }
    int GetIndex() { return nodeIndex; }
    bool IsInitialised() { return isInitialised; }

protected:
    class Game* game;
    Node* parent = nullptr;

    virtual void PhysicsUpdate(float delta) { }
    virtual void RenderingUpdate() { }

    Vector2 position = { 0, 0 };

    // used to keep track of which node is which in the nodes array in Game.h
    int nodeIndex = -1;
    
    bool isInitialised = false;
};

