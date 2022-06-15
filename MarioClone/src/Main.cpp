#include "Main.h"

int main()
{
    Game game;

    InitWindow(1024, 960, "Superb Run 'n' Jump Sibling");

    game.InitGame();

    while (!WindowShouldClose())
    {
        game.Update();
        game.Draw();
    }

    game.EndGame();

    CloseWindow();
    return 0;
}