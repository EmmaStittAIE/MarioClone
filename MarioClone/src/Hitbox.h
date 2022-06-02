#pragma once

#include <raylib.h>
#include <raymath.h>

#include "Exceptions.h"
#include "Node.h"

enum class Alignment
{
    topLeft,
    topRight,
    bottomLeft,
    bottomRight,
    centre
};

enum class Sides
{
    left = 1,
    right = 2,
    top = 4,
    bottom = 8
};

inline Sides operator|(Sides lhs, Sides rhs)
{
    return static_cast<Sides>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

inline Sides operator&(Sides lhs, Sides rhs)
{
    return static_cast<Sides>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

inline Sides operator|=(Sides& lhs, Sides rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

class Hitbox : public Node
{
public:
    Hitbox(Game* gamePointer, Rectangle rect, Node* parentPointer);
    Hitbox(Game* gamePointer, Rectangle rect)
        : Hitbox(gamePointer, rect, nullptr) {}
    
    Hitbox(Game* gamePointer, Vector2 pos, Vector2 size, Node* parent)
        : Hitbox(gamePointer, { pos.x, pos.y, size.x, size.y }, parent) {}
    Hitbox(Game* gamePointer, Vector2 pos, Vector2 size)
        : Hitbox(gamePointer, { pos.x, pos.y, size.x, size.y }, nullptr) {}

    Vector2 GetPos() override { return topLeft; }

    Vector2 GetTopLeft() { return topLeft; }
    Vector2 GetTopRight() { return { bottomRight.x, topLeft.y }; }
    Vector2 GetBottomLeft() { return { topLeft.x, bottomRight.y }; }
    Vector2 GetBottomRight() { return bottomRight; }

    Vector2 GetSize() { return Vector2Subtract(bottomRight, topLeft); }
    float GetWidth() { return bottomRight.x - topLeft.x; }
    float GetHeight() { return bottomRight.y - topLeft.y; }

    float GetLeft() { return topLeft.x; }
    float GetRight() { return bottomRight.x; }
    float GetTop() { return topLeft.y; }
    float GetBottom() { return bottomRight.y; }

    bool CheckCollision(Hitbox other);
    Sides GetSidesColliding(Hitbox other);

    void Move(Vector2 amount);
    void SetPos(Vector2 pos);

    void SetScale(Vector2 newSize, Alignment align);

    Color GetDebugColour() { return debugColour; }
    void SetDebugColour(Color colour) { debugColour = colour; }

private:
    Vector2 topLeft;
    Vector2 bottomRight;

    Color debugColour = {255, 255, 255, 255};
};

