#include "Hitbox.h"

Hitbox::Hitbox(Game* gamePointer, Rectangle rect, Node* parentPointer)
    : Node(gamePointer)
{
    topLeft = { rect.x, rect.y };
    bottomRight = Vector2Add(topLeft, { rect.width, rect.height });

    parent = parentPointer;
}

bool Hitbox::CheckCollision(Hitbox other)
{
    return GetLeft() < other.GetRight() &&
           GetRight() > other.GetLeft() &&
           GetTop() < other.GetBottom() &&
           GetBottom() > other.GetTop();
}

Sides Hitbox::GetSidesColliding(Hitbox other)
{
    Sides sides = static_cast<Sides>(0);
    
    if (GetLeft() < other.GetRight() && GetRight() > other.GetRight()) { sides |= Sides::left; }
    if (GetRight() > other.GetLeft() && GetLeft() < other.GetLeft()) { sides |= Sides::right; }
    if (GetTop() < other.GetBottom() && GetBottom() > other.GetBottom()) { sides |= Sides::top; }
    if (GetBottom() > other.GetTop() && GetTop() < other.GetTop()) { sides |= Sides::bottom; }
    return sides;
}

void Hitbox::Move(Vector2 amount)
{
    topLeft = Vector2Add(topLeft, amount);
    bottomRight = Vector2Add(bottomRight, amount);
}

void Hitbox::SetPos(Vector2 pos)
{
    Vector2 size = GetSize();
    topLeft = pos;
    bottomRight = Vector2Add(pos, size);
}

void Hitbox::SetScale(Vector2 newSize, Alignment align)
{
    switch (align)
    {
    case Alignment::topLeft:
        bottomRight = Vector2Add(topLeft, newSize);
        break;

    case Alignment::topRight:
        topLeft.x = bottomRight.x - newSize.x;
        bottomRight.y = topLeft.y + newSize.y;
        break;

    case Alignment::bottomLeft:
        bottomRight.x = topLeft.x + newSize.x;
        topLeft.y = bottomRight.y - newSize.y;
        break;

    case Alignment::bottomRight:
        topLeft = Vector2Subtract(bottomRight, newSize);
        break;

    case Alignment::centre:
        topLeft = Vector2Add(topLeft, Vector2Scale(newSize, 0.5f));
        break;

    default:
        throw ArgumentException("align");
        break;
    }
}
