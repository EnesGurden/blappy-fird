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
    const int BirdInitialX = 400;
    const int BirdInitialY = 225;
    const int ObstacleUpDownInitHeight = GetRandomValue(0, 150);
    const int ObstacleUpDownInitWidth = 150;
    const int ObstacleUpDownInitX = 400;
    const int ObstacleUpInitY = 0;
    const int ObstacleDownInitY = ScreenHeight - ObstacleUpDownInitHeight;
    Vector2 bird = { .x = BirdInitialX, .y = BirdInitialY };
    Rectangle ObstacleUp = { .height = ObstacleUpDownInitHeight, .width = ObstacleUpDownInitWidth, .x = ObstacleUpDownInitX, .y = ObstacleUpInitY };
    Rectangle ObstacleDown = { .height = ObstacleUpDownInitHeight, .width = ObstacleUpDownInitWidth, .x = ObstacleUpDownInitX, .y = ObstacleDownInitY };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        if (IsKeyDown(KEY_UP)) {
            bird.y -= 2;
        }
        bird.y++;
        ObstacleUp.x--;
        ObstacleDown.x--;
        if (ObstacleUp.x == -ObstacleUp.width) {
            ObstacleUp.x = ScreenWidth;
            ObstacleDown.x = ScreenWidth;
        }
        DrawRectangleRec(ObstacleUp, GREEN);
        DrawRectangleRec(ObstacleDown, GREEN);
        DrawTexture(birdTex, bird.x, bird.y, WHITE);
        Vector2 kusCenter = { .x = bird.x + birdTex.width / 2, .y = bird.y + birdTex.height / 2 };
        if (CheckCollisionCircleRec(kusCenter, birdTex.height / 2, ObstacleDown) || CheckCollisionCircleRec(kusCenter, birdTex.height / 2, ObstacleUp)) {
            bird.x = BirdInitialX;
            bird.y = BirdInitialY;
            ObstacleUp.x = ObstacleUpDownInitX;
            ObstacleUp.y = ObstacleUpInitY;
            ObstacleDown.x = ObstacleUpDownInitX;
            ObstacleDown.y = ObstacleDownInitY;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
