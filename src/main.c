#include <math.h>
#include <raylib.h>
#include <stdio.h>

#define PROJECT_NAME "blappy-fird"
typedef struct {
    Rectangle top;
    Rectangle bottom;
} Obstacle;

typedef struct
{
    Vector2 pos;
    float speedY;
} Bird;

const int ObstacleTopY
    = 0;
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
    Bird bird = { .pos = { .x = BirdInitialX, .y = BirdInitialY }, .speedY = 0 };

    const int ObstacleGap = 150;
    const int ObstacleSpacing = 150;
    const int NumObstacles = 4;
    Obstacle obstacles[NumObstacles];
    for (int i = 0; i < NumObstacles; i++) {
        ResetObstacle(&obstacles[i], ScreenWidth + i * (ObstacleWidth + ObstacleSpacing), ScreenHeight, ObstacleGap);
    }

    int score = 0;
    char scoreText[20];
    const float MaxHeightTime = 0.5;
    const float MaxHeight = ObstacleWidth + ObstacleSpacing / 2;
    const float Gravity = 2 * MaxHeight / MaxHeightTime / MaxHeightTime;
    const float ObstacleSpeed = 2.5;
    float dt = 1.0 / 60.0;
    const float ThicknessRound = 0.5;
    const float ThicknessLine = 0.3;
    const int RoundedHeight = 20;
    const int RoundedWidth = ObstacleWidth + 10;
    const int Segment = 6;
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        const char* MenuOptions[] = { "Start Game", "About", "Exit" };
        const int MenuOptionsNumber = sizeof(MenuOptions) / sizeof(MenuOptions[0]);
        const int MenuFontSize = 20;
        const int MenuVerticalSpace = 40;
        const int MenuInitialY = 175;
        enum Menu {
            SCREENHOME,
            SCREENABOUT,
            SCREENEXIT,
            SCREENGAME
        };
        static int menuIndex = 0;
        static int selectedMenuIndex = 0;

        switch (selectedMenuIndex) {
        case SCREENHOME:
            if (IsKeyPressed(KEY_UP)) {
                menuIndex--;
                if (menuIndex < 0)
                    menuIndex = MenuOptionsNumber - 1;
            }
            if (IsKeyPressed(KEY_DOWN)) {
                menuIndex++;
                if (menuIndex == MenuOptionsNumber)
                    menuIndex = 0;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                selectedMenuIndex = menuIndex;
                if (selectedMenuIndex == 0) {
                    selectedMenuIndex = SCREENGAME;
                } else {
                    menuIndex = 0;
                }
            }
            for (int i = 0; i < MenuOptionsNumber; i++) {
                Color color = (i == menuIndex) ? YELLOW : DARKGRAY;
                DrawText(MenuOptions[i], ScreenWidth / 2 - MeasureText(MenuOptions[i], MenuFontSize) / 2, MenuInitialY + i * MenuVerticalSpace, MenuFontSize, color);
            }
            break;
        case SCREENABOUT:
            DrawText("DEVELOPERS\0}", 250, 50, 50, DARKBLUE);
            DrawText("Abdulkerim ELMAS\nEnes GURDEN\0}", 225, 115, 30, LIGHTGRAY);
            DrawText("VERSION\0}", 250, 230, 50, DARKBLUE);
            DrawText("1.0.0\0}", 240, 295, 30, LIGHTGRAY);
            if (IsKeyPressed(KEY_BACKSPACE)) {
                selectedMenuIndex = SCREENHOME;
            }
            break;
        case SCREENEXIT:
            CloseWindow(); // ask senior WARNING: GLFW: Error: 65537 Description: The GLFW library is not initialized
            break;
        case SCREENGAME:
            if (IsKeyPressed(KEY_UP)) {
                bird.speedY = -sqrt(Gravity * MaxHeight);
            }

            bird.pos.y = bird.pos.y + bird.speedY * dt;
            bird.speedY = bird.speedY + Gravity * dt;

            for (int i = 0; i < NumObstacles; i++) {
                obstacles[i].top.x -= ObstacleSpeed;
                obstacles[i].bottom.x -= ObstacleSpeed;
                if (obstacles[i].top.x == -obstacles[i].top.width) {
                    ResetObstacle(&obstacles[i], ScreenWidth, ScreenHeight, ObstacleGap);
                }
                if (obstacles[i].top.x + ObstacleWidth == bird.pos.x) {
                    score++;
                }
                snprintf(scoreText, sizeof(scoreText), "Score \n\t %d", score);
            }

            Vector2 birdCenter = { .x = bird.pos.x + birdTex.width / 2, .y = bird.pos.y + birdTex.height / 2 };
            for (int i = 0; i < NumObstacles; i++) {
                if ((bird.pos.y > ScreenHeight) || CheckCollisionCircleRec(birdCenter, birdTex.height / 2, obstacles[i].top) || CheckCollisionCircleRec(birdCenter, birdTex.height / 2, obstacles[i].bottom)) {
                    bird.pos.x = BirdInitialX;
                    bird.pos.y = BirdInitialY;
                    for (int j = 0; j < NumObstacles; j++) {
                        ResetObstacle(&obstacles[j], ScreenWidth + j * (ObstacleWidth + ObstacleSpacing), ScreenHeight, ObstacleGap);
                    }
                    score = 0;
                    bird.speedY = 0;
                }
            }

            for (int i = 0; i < NumObstacles; i++) {
                DrawRectangleRec(obstacles[i].top, GREEN);
                DrawRectangleRec(obstacles[i].bottom, GREEN);

                Rectangle borderRoundedTop = { .height = RoundedHeight, .width = RoundedWidth, .x = obstacles[i].top.x - (RoundedWidth - ObstacleWidth) / 2, .y = obstacles[i].top.height - RoundedHeight };
                DrawRectangleRounded(borderRoundedTop, ThicknessRound, Segment, GREEN);
                DrawRectangleRoundedLinesEx(borderRoundedTop, ThicknessRound, Segment, ThicknessLine, DARKGRAY);
                DrawLine(obstacles[i].top.x, obstacles[i].top.y, obstacles[i].top.x, obstacles[i].top.height - borderRoundedTop.height, BLACK);
                DrawLine(obstacles[i].top.x + ObstacleWidth, obstacles[i].top.y, obstacles[i].top.x + ObstacleWidth, obstacles[i].top.height - borderRoundedTop.height, BLACK);
                Rectangle borderRoundedBottom = { .height = RoundedHeight, .width = RoundedWidth, .x = obstacles[i].bottom.x - (RoundedWidth - ObstacleWidth) / 2, .y = obstacles[i].bottom.y };
                DrawRectangleRounded(borderRoundedBottom, ThicknessRound, Segment, GREEN);
                DrawRectangleRoundedLinesEx(borderRoundedBottom, ThicknessRound, Segment, ThicknessLine, DARKGRAY);
                DrawLine(obstacles[i].bottom.x, obstacles[i].bottom.y + borderRoundedBottom.height, obstacles[i].bottom.x, ScreenHeight, BLACK);
                DrawLine(obstacles[i].bottom.x + ObstacleWidth, obstacles[i].bottom.y + borderRoundedBottom.height, obstacles[i].bottom.x + ObstacleWidth, ScreenHeight, BLACK);
            }
            DrawTexture(birdTex, bird.pos.x, bird.pos.y, WHITE);
            DrawText(scoreText, 350, 50, 50, LIGHTGRAY);
            break;
        default:
            break;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            menuIndex = SCREENHOME;
            selectedMenuIndex = SCREENHOME;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
