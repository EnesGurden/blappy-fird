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

    Texture2D birdTex = LoadTexture("resources/bird.png");
    int BirdX = 400;
    int BirdY = 225;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        if (IsKeyDown(KEY_UP)) {
            BirdY--;
        }
        if (IsKeyDown(KEY_DOWN)) {
            BirdY++;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            BirdX++;
        }
        if(IsKeyDown(KEY_LEFT)) {
            BirdX--;
        }
        DrawTexture(birdTex, BirdX, BirdY, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
