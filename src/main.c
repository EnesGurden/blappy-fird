#include <raylib.h>
#include <stdio.h>

#define PROJECT_NAME "blappy-fird"
typedef struct {
    Rectangle top;
    Rectangle bottom;
} Obstacle;

const int ObstacleTopY = 0;
const int ObstacleWidth = 100;

void ResetObstacle(Obstacle* obstacle, float startX, float screenHeight, float gapHeight)
{
    obstacle->top.height = GetRandomValue(gapHeight / 2, screenHeight - gapHeight * 2);
    obstacle->top.width = ObstacleWidth;
    obstacle->top.x = startX;
    obstacle->top.y = ObstacleTopY;

    obstacle->bottom.height = screenHeight - obstacle->top.height - gapHeight;
    obstacle->bottom.width = ObstacleWidth;
    obstacle->bottom.x = startX;
    obstacle->bottom.y = screenHeight - obstacle->bottom.height;
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    const int ScreenWidth = 900;
    const int ScreenHeight = 450;
    InitWindow(ScreenWidth, ScreenHeight, PROJECT_NAME);

    const int FpsValue = 60;
    SetTargetFPS(FpsValue);

    Texture2D birdTex = LoadTexture("resources/bird.png");
    const int BirdInitialX = 300;
    const int BirdInitialY = 225;
    Vector2 bird = { .x = BirdInitialX, .y = BirdInitialY };

    const int ObstacleGap = 100; // vertical
    const int ObstacleSpacing = 100; // horizontal
    const int NumObstacles = 5;
    Obstacle obstacles[NumObstacles];
    for (int i = 0; i < NumObstacles; i++) {
        ResetObstacle(&obstacles[i], ScreenWidth + i * (ObstacleWidth + ObstacleSpacing), ScreenHeight, ObstacleGap);
    }

    int score = 0;
    char scoreText[20];
    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_UP)) {
            bird.y -= 2;
        }
        bird.y += 1;

        for (int i = 0; i < NumObstacles; i++) {
            obstacles[i].top.x--;
            obstacles[i].bottom.x--;
            if (obstacles[i].top.x == -obstacles[i].top.width) {
                ResetObstacle(&obstacles[i], ScreenWidth, ScreenHeight, ObstacleGap);
            }
            if (obstacles[i].top.x + ObstacleWidth == bird.x) {
                score++;
            }
            snprintf(scoreText, sizeof(scoreText), "Score \n\t %d", score);
        }

        Vector2 birdCenter = { .x = bird.x + birdTex.width / 2, .y = bird.y + birdTex.height / 2 };
        for (int i = 0; i < NumObstacles; i++) {
            if (CheckCollisionCircleRec(birdCenter, birdTex.height / 2, obstacles[i].top) || CheckCollisionCircleRec(birdCenter, birdTex.height / 2, obstacles[i].bottom)) {
                bird.x = BirdInitialX;
                bird.y = BirdInitialY;
                for (int j = 0; j < NumObstacles; j++) {
                    ResetObstacle(&obstacles[j], ScreenWidth + j * (ObstacleWidth + ObstacleSpacing), ScreenHeight, ObstacleGap);
                }
                score = 0;
            }
        }

        BeginDrawing();
        ClearBackground(SKYBLUE);
        for (int i = 0; i < NumObstacles; i++) {
            DrawRectangleRec(obstacles[i].top, GREEN);
            DrawRectangleRec(obstacles[i].bottom, GREEN);
        }
        DrawTexture(birdTex, bird.x, bird.y, WHITE);
        DrawText(scoreText, 350, 50, 50, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
