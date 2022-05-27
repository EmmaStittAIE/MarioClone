#pragma once

#include "Exceptions.h"
#include "Sprite.h"

class GameObject
{
public:
    Sprite sprite;

    void Init(Texture* spritesheetPointer);

    void PUpdate(float delta);
    void RUpdate(float delta);

    Vector2 GetPos() { return position; }

protected:
    virtual void PhysicsUpdate(float delta) { }
    virtual void RenderingUpdate(float delta) { }

    Vector2 position = {500, 500};
};

