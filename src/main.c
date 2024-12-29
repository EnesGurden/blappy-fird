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
    Vector2 bird = { .x = 400, .y = 225 };
    const Rectangle ObstacleUp = { .height = 150, .width = 150, .x = 400, .y = 0 };
    const Rectangle ObstacleDown = { .height = 150, .width = 150, .x = 400, .y = 350 };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        if (IsKeyDown(KEY_UP)) {
            bird.y -= 2;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            bird.x++;
        }
        if (IsKeyDown(KEY_LEFT)) {
            bird.x--;
        }
        bird.y++;
        DrawRectangleRec(ObstacleUp, GREEN);
        DrawRectangleRec(ObstacleDown, GREEN);
        DrawTexture(birdTex, bird.x, bird.y, WHITE);
        Vector2 kusCenter = { .x = bird.x + birdTex.width / 2, .y = bird.y + birdTex.height / 2 };
        if (CheckCollisionCircleRec(kusCenter, birdTex.height / 2, ObstacleDown) || CheckCollisionCircleRec(kusCenter, birdTex.height / 2, ObstacleUp)) {
            DrawText("GAME OVER!", 62, 62, 62, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
