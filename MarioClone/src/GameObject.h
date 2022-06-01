#pragma once

#include "Exceptions.h"
#include "Sprite.h"
#include "Hitbox.h"

class GameObject
{
public:
    Hitbox hitbox;
    Sprite sprite;

    GameObject(Texture* spritesheetPointer, Rectangle hitboxRect);

    void PUpdate(float delta);
    void RUpdate(float delta);

    Vector2 GetPos() { return position; }

protected:
    virtual void PhysicsUpdate(float delta) { }
    virtual void RenderingUpdate(float delta) { }

    Vector2 position = {500, 500};
};

