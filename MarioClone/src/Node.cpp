#include "Node.h"
#include "Game.h"

Node::Node(Game* gamePointer)
{
    game = gamePointer;

    isInitialised = game->AddNode(this);
}

Node::Node(Game* gamePointer, Node* parentPointer)
{
    game = gamePointer;

    isInitialised = game->AddNode(this);

    parent = parentPointer;
}

void Node::PUpdate(float delta)
{
    // stuff to do for every object
    PhysicsUpdate(delta);
}

void Node::RUpdate()
{
    // stuff to do for every object
    RenderingUpdate();
}