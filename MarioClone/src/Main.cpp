#include "Main.h"

int main()
{
    Game game;

    InitWindow(1024, 960, "I love resetting an entire project TvT");
    SetWindowState(FLAG_WINDOW_UNDECORATED);

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