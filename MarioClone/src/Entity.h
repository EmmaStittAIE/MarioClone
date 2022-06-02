#pragma once

#include <typeindex>

#include <raylib.h>
#include <raymath.h>

#include "GameObject.h"
#include "Hitbox.h"

class Entity : public GameObject
{
public:
    Entity(Game* gamePointer, Node* parentPointer, Texture* spritesheetPointer, Rectangle hitboxRect);

    void Move(Vector2 translation);
    void Move(float x, float y) { Move({ x, y }); }

    void SetPos(Vector2 pos);
    void SetPos(float x, float y) { SetPos({ x, y }); }

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
    Vector2 previousPos = position;

    Vector2 velocity = {0, 0};
    Vector2 maxWalkSpeed = { 7, 20 };
    Vector2 maxRunSpeed = { 10, 20 };

    float walkVelocity = 30;
    float runVelocity = 40;

    float gravity = 50;
    float friction = 10;

    bool running = false;
    bool onFloor = false;
};

