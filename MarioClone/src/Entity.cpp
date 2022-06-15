#include "Entity.h"

void Entity::PhysicsUpdate(float delta)
{
    if (velocity.x > 0.4 || velocity.x < -0.4)
    {
        if ((velocity.x > 0 && !sprite->GetFacingRight()) || (velocity.x < 0 && sprite->GetFacingRight())) { sprite->SetAnimation(2); }
        else if (sprite->GetCurrentAnimIndex() != 1) { sprite->SetAnimation(1); }
    }
    else { sprite->SetAnimation(0); }

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
    
    if (!onFloor) { sprite->SetAnimation(3); }

    Move(velocity);

    onFloor = false;
}

Entity::Entity(Game* gamePointer, Texture* spritesheetPointer, Rectangle hitboxRect)
    : GameObject(gamePointer, spritesheetPointer, hitboxRect)
{
}

Entity::Entity(Game* gamePointer, Node* parentPointer, Texture* spritesheetPointer, Rectangle hitboxRect)
    : GameObject(gamePointer, parentPointer, spritesheetPointer, hitboxRect)
{
}

void Entity::AddForce(Vector2 force, float delta)
{
    velocity = velocity + (force * delta);
}

void Entity::SetForce(Vector2 force)
{
    velocity = force;
}

void Entity::HandleInput(float delta)
{
    if (IsKeyDown(KEY_LEFT))
    {
        AddForce(-(running ? runAccel : walkAccel), 0, delta);
        if (onFloor) { sprite->SetFacingRight(false); }
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        AddForce((running ? runAccel : walkAccel), 0, delta);
        if (onFloor) { sprite->SetFacingRight(true); }
    }
    if (IsKeyPressed(KEY_Z))
    {
        if (onFloor) { SetForce(velocity.x, -20); }
    }
    if (IsKeyDown(KEY_X))
    {
        running = true;
    }
}

// TODO: redo entity collision handling
void Entity::HandleCollision(Hitbox& thisBox, Hitbox& collision)
{
    if (collision.GetParent() == nullptr || typeid(*collision.GetParent()) != typeid(Entity))
    {
        Sides entitySides = thisBox.GetSidesColliding(collision);

        if ((entitySides & Sides::bottom) == Sides::bottom)
        {
            SetPos(position.x, collision.GetTop() - thisBox.GetHeight());
            velocity.y = 0;
            onFloor = true;
        }
        else if ((entitySides & Sides::top) == Sides::top)
        {
            SetPos(position.x, collision.GetBottom());
            velocity.y = 0;
        }

        entitySides = hitbox->GetSidesColliding(collision);
        if ((entitySides & Sides::left) == Sides::left)
        {
            SetPos(collision.GetRight(), position.y);
            velocity.x = 0;
        }
        else if ((entitySides & Sides::right) == Sides::right)
        {
            SetPos(collision.GetLeft() - hitbox->GetWidth(), position.y);
            velocity.x = 0;
        }
    }
}
