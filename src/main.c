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
        const int BirdX = 400;
        const int BirdY = 225;
        const int BirdWidth = 50;
        const int BirdHeight = 20;
        DrawRectangle(BirdX, BirdY, BirdWidth, BirdHeight, YELLOW);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
