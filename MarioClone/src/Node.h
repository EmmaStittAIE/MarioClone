#pragma once

#include <raylib.h>

#include "RaylibOperatorOverrides.h"

class Node
{
public:
    Node(class Game* gamePointer);
    Node(Game* gamePointer, Node* parentPointer);
    void InitNode(int index) { nodeIndex = index; }
    bool AddChild(Node* node);

    void PUpdate(float delta);
    void RUpdate();
    void DrawNode(const double alpha);

    virtual void HandleCollision(class Hitbox& thisBox, Hitbox& collision) {}

    virtual void SetPrevPosAll();

    virtual void SetPos(Vector2 pos);
    void SetPos(float x, float y) { SetPos({ x, y }); }

    virtual void Move(Vector2 translation);
    void Move(float x, float y) { Move({ x, y }); }

    Node* GetParent() { return parent; }
    Node** GetChildren() { return children; }
    int GetNumOfChildren() { return numOfChildren; }
    virtual Vector2 GetPos() { return position; }
    virtual Vector2 GetPrevPos() { return previousPos; }
    int GetIndex() { return nodeIndex; }
    bool IsInitialised() { return isInitialised; }

protected:
    class Game* game;
    Node* parent = nullptr;

    int numOfChildren = 0;
    int maxNumOfChildren = 100;
    Node** children = new Node * [maxNumOfChildren] {};

    virtual void PhysicsUpdate(float delta) { }
    virtual void RenderingUpdate() { }
    virtual void SetPrevPos() { previousPos = position; }
    virtual void Draw(const double alpha) {}

    Vector2 previousPos = { 0, 0 };
    Vector2 position = { 0, 0 };

    // used to keep track of which node is which in the nodes array in Game.h
    int nodeIndex = -1;
    
    bool isInitialised = false;
};

