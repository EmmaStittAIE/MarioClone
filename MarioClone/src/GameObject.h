#pragma once

#include "Exceptions.h"
#include "Sprite.h"
#include "Hitbox.h"
#include "Node.h"

class GameObject : public Node
{
public:
    Hitbox* hitbox;
    Sprite* sprite;

    GameObject(Game* gamePointer, Node* parentPointer, Texture* spritesheetPointer, Rectangle hitboxRect);
};

