#include "Node.h"
#include "Game.h"

Node::Node(Game* gamePointer)
    : game(gamePointer)
{
    isInitialised = game->AddNode(this);
}

Node::Node(Game* gamePointer, Node* parentPointer)
    : game(gamePointer),
      parent(parentPointer)
{
    if (parent == nullptr) { throw NotInitialisedException(); }
    parent->AddChild(this);
}

bool Node::AddChild(Node* node)
{
    if (node->IsInitialised())
    {
        std::cout << "Failed to add child - node already exists" << std::endl;
        return false;
    }

    for (int i = 0; i < maxNumOfChildren; i++)
    {
        if (children[i] == nullptr)
        {
            children[i] = node;
            node->InitNode(i);
            numOfChildren++;

            return true;
        }
    }

    std::cout << "Failed to add child - array too small" << std::endl;
    return false;
}

void Node::PUpdate(float delta)
{
    SetPrevPos();

    // stuff to do for every node
    PhysicsUpdate(delta);
    for (int i = 0; i < numOfChildren; i++)
    {
        children[i]->PUpdate(delta);
    }
}

void Node::RUpdate()
{
    // stuff to do for every node
    RenderingUpdate();
    for (int i = 0; i < numOfChildren; i++)
    {
        children[i]->RUpdate();
    }
}

void Node::DrawNode(const double alpha)
{
    // stuff to do for every node
    Draw(alpha);
    for (int i = 0; i < numOfChildren; i++)
    {
        children[i]->Draw(alpha);
    }
}

void Node::SetPrevPos()
{
    previousPos = position;
}

void Node::SetPos(Vector2 pos)
{
    position = pos;
    for (int i = 0; i < numOfChildren; i++)
    {
        children[i]->Move(pos - children[i]->GetPos());
    }
}

void Node::Move(Vector2 translation)
{
    position = position + translation;
    for (int i = 0; i < numOfChildren; i++)
    {
        children[i]->Move(translation);
    }
}
