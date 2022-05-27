#pragma once

#include <raylib.h>
#include <raymath.h>

#include "GameObject.h"

class Entity : public GameObject
{
public:
    void Move(Vector2 translation);
    void Move(float x, float y) { Move({ x, y }); }

    void AddForce(Vector2 force, float delta);
    void AddForce(float x, float y, float delta) { AddForce({ x, y }, delta); }

    void HandleInput(float delta);

    Vector2 GetVelocity() { return velocity; };

protected:
    void PhysicsUpdate(float delta) override;

private:
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

