#pragma once

#include <typeindex>

#include <raylib.h>

#include "RaylibOperatorOverrides.h"
#include "GameObject.h"
#include "Hitbox.h"

class Entity : public GameObject
{
public:
    Entity(Game* gamePointer, Texture* spritesheetPointer, Rectangle hitboxRect);
    Entity(Game* gamePointer, Node* parentPointer, Texture* spritesheetPointer, Rectangle hitboxRect);

    void AddForce(Vector2 force, float delta);
    void AddForce(float x, float y, float delta) { AddForce({ x, y }, delta); }

    void SetForce(Vector2 force);
    void SetForce(float x, float y) { SetForce({ x, y }); }

    void HandleInput(float delta);
    void HandleCollision(Hitbox& thisBox, Hitbox& collision) override;

    Vector2 GetVelocity() { return velocity; };

protected:
    void PhysicsUpdate(float delta) override;

private:
    Vector2 velocity = {0, 0};
    Vector2 maxWalkSpeed = { 7, 20 };
    Vector2 maxRunSpeed = { 10, 20 };

    float walkAccel = 30;
    float runAccel = 40;

    float gravity = 50;
    float friction = 10;

    bool running = false;
    bool onFloor = false;
};

