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
        const int BirdX = 190;
        const int BirdY = 200;
        DrawRectangle(BirdX, BirdY, 50, 20, YELLOW);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
