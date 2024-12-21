#include <raylib.h>

#define PROJECT_NAME "blappy-fird"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    const int ScreenWidth = 800;
    const int ScreenHeight = 450;
    InitWindow(ScreenWidth, ScreenHeight, PROJECT_NAME);

    const int FpsValue = 60;
    SetTargetFPS(FpsValue);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        const int FontSize = 20;
        const int CoordinateTextX = 190;
        const int CoordinateTextY = 200;
        DrawText("Congrats! You created your first window!", CoordinateTextX, CoordinateTextY, FontSize, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
