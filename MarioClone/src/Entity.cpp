#include "Entity.h"

void Entity::PhysicsUpdate(float delta)
{
    previousPos = position;

    if (velocity.x > 0.4 || velocity.x < -0.4)
    {
        if ((velocity.x > 0 && !sprite.GetFacingRight()) || (velocity.x < 0 && sprite.GetFacingRight())) { sprite.SetAnimation(2); }
        else if (sprite.GetCurrentAnimIndex() != 1) { sprite.SetAnimation(1); }
    }
    else { sprite.SetAnimation(0); }

    running = false;

    HandleInput(delta);

    // apply gravity
    AddForce(0, gravity, delta);

    // apply friction
    if (velocity.x > 0.4 || velocity.x < -0.4) { AddForce((velocity.x > 0) ? -friction : friction, 0, delta); }
    else { velocity.x = 0; }

    // clamp to max speed
    Vector2 maxSpeed = running ? maxRunSpeed : maxWalkSpeed;
    velocity = { Clamp(velocity.x, -maxSpeed.x, maxSpeed.x),
                 Clamp(velocity.y, -INFINITY, maxSpeed.y) };
    
    if (!onFloor) { sprite.SetAnimation(3); }

    Move(velocity);

    onFloor = false;
}

Entity::Entity(Texture* spritesheetPointer, Rectangle hitboxRect)
    : GameObject(spritesheetPointer, hitboxRect)
{
}

void Entity::Move(Vector2 translation)
{
    position = Vector2Add(position, translation);
    hitbox.SetPos(position);
}

void Entity::SetPos(Vector2 pos)
{
    position = pos;
    hitbox.SetPos(position);
}

void Entity::AddForce(Vector2 force, float delta)
{
    velocity = Vector2Add(velocity, Vector2Scale(force, delta));
}

void Entity::HandleInput(float delta)
{
    if (IsKeyDown(KEY_LEFT))
    {
        AddForce(-(running ? runVelocity : walkVelocity), 0, delta);
        if (onFloor) { sprite.SetFacingRight(false); }
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        AddForce(running ? runVelocity : walkVelocity, 0, delta);
        if (onFloor) { sprite.SetFacingRight(true); }
    }
    if (IsKeyPressed(KEY_Z))
    {
        if (onFloor) { AddForce(0, -20, 1); }
    }
    if (IsKeyDown(KEY_X))
    {
        running = true;
    }
}

void Entity::HandleCollision(Hitbox collision, Sides entitySides)
{
    if ((entitySides & Sides::bottom) == Sides::bottom)
    {
        SetPos(position.x, collision.GetTop() - hitbox.GetHeight());
        velocity.y = 0;
        onFloor = true;
    }

    entitySides = hitbox.GetSidesColliding(collision);
    if ((entitySides & Sides::left) == Sides::left)
    {
        SetPos(collision.GetRight(), position.y);
        velocity.x = 0; 
    }
    else if ((entitySides & Sides::right) == Sides::right)
    {
        SetPos(collision.GetLeft() - hitbox.GetWidth(), position.y);
        velocity.x = 0;
    }
    
    
}
