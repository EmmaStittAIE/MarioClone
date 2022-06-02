#include "GameObject.h"

GameObject::GameObject(Game* gamePointer, Node* parentPointer, Texture* spritesheetPointer, Rectangle hitboxRect)
    : Node(gamePointer)
{
    hitbox = new Hitbox{ gamePointer, hitboxRect, this };
    hitbox->SetDebugColour({ 255, 0, 0, 120 });
    sprite = new Sprite{ gamePointer, spritesheetPointer, this };
}