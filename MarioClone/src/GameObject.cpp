#include "GameObject.h"

GameObject::GameObject(Game* gamePointer, Texture* spritesheetPointer, Rectangle hitboxRect)
    : Node(gamePointer)
{
    hitbox = new Hitbox{ gamePointer, this, hitboxRect };
    hitbox->SetDebugColour({ 255, 0, 0, 120 });
    sprite = new Sprite{ gamePointer, this, spritesheetPointer };
}

GameObject::GameObject(Game* gamePointer, Node* parentPointer, Texture* spritesheetPointer, Rectangle hitboxRect)
    : Node(gamePointer, parentPointer)
{
    hitbox = new Hitbox{ gamePointer, this, hitboxRect };
    hitbox->SetDebugColour({ 255, 0, 0, 120 });
    sprite = new Sprite{ gamePointer, this, spritesheetPointer };
}