#include "Entity.h"

void Entity::PhysicsUpdate(float delta)
{
    if (position.x <= 0 || position.x >= GetScreenWidth() - 64) { velocity.x = 0; }
    if (velocity.x > 0.4 || velocity.x < -0.4)
    {
        if (((velocity.x > 0 && !sprite.GetFacingRight()) || (velocity.x < 0 && sprite.GetFacingRight())) && sprite.GetCurrentAnimIndex() != 2) { sprite.SetAnimation(2); }
        else if (sprite.GetCurrentAnimIndex() != 1) { sprite.SetAnimation(1); }
    }
    else if (sprite.GetCurrentAnimIndex() != 0) { sprite.SetAnimation(0); }

    running = false;

    HandleInput(delta);

    // apply gravity
    AddForce(0, gravity, delta);

    // apply friction
    if (velocity.x > 0.4 || velocity.x < -0.4) { AddForce((velocity.x > 0) ? -friction : friction, 0, delta); }
    else { velocity.x = 0; }

    onFloor = false;
    // clamp to max speed
    Vector2 maxSpeed = running ? maxRunSpeed : maxWalkSpeed;
    velocity = { Clamp(velocity.x, -maxSpeed.x, maxSpeed.x),
                 Clamp(velocity.y, -INFINITY, maxSpeed.y) };
    
    if (position.y >= GetScreenHeight() - 64) { onFloor = true; }

    if (onFloor) { velocity.y = std::min(velocity.y, 0.0f); }
    else if (sprite.GetCurrentAnimIndex() != 3) { sprite.SetAnimation(3); }

    position = Vector2Add(velocity, position);

    position = { Clamp(position.x, 0, GetScreenWidth() - 64),
                 Clamp(position.y, 0, GetScreenHeight() - 64) };
}

void Entity::Move(Vector2 translation)
{
    position = Vector2Add(position, translation);
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