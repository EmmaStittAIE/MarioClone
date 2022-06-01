#include "GameObject.h"

GameObject::GameObject(Texture* spritesheetPointer, Rectangle hitboxRect)
    : hitbox{ hitboxRect, this }
{
    sprite.SetParent(this);
    sprite.SetSpritesheet(spritesheetPointer);
}

void GameObject::PUpdate(float delta)
{
    // stuff to do for every object
    PhysicsUpdate(delta);
}

void GameObject::RUpdate(float delta)
{
    // stuff to do for every object
    sprite.AdvanceAnimation(delta);
    RenderingUpdate(delta);
}