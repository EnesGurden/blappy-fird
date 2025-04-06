#include <raylib.h>

#include <cmath>
#include <cstdio>

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

typedef struct {
    float startX;
    float obstacleHeight;
    float gapHeight;
} ObstacleConfig;

const float Half = 2.0F;
const int ScreenWidth = 900;
const int ScreenHeight = 450;
const int FpsValue = 60;

const float BirdInitialX = 300.0F;
const float BirdInitialY = 225.0F;
Bird bird;

int score = 0;
enum {
    NUMOBSTACLES = 4,
    SCOREBUFFERCOUNT = 21,
};
char scoreText[SCOREBUFFERCOUNT];

const int ObstacleTopY = 0;
const float ObstacleWidth = 100;
const float ObstacleSpacing = 150;
const float ObstacleGap = 150.0F;
const float ObstacleSpeed = 2.5F;
Obstacle obstacles[NUMOBSTACLES];

const float MaxHeight = ObstacleWidth + (ObstacleSpacing / Half);
const float MaxHeightTime = 0.5F;
const float Gravity = 2 * MaxHeight / MaxHeightTime / MaxHeightTime;
float deltaT = 1.0F / (float)FpsValue;

const float ThicknessRound = 0.5F;
const float ThicknessLine = 0.3F;
const float RoundedHeight = 20;
const float RoundedWidth = ObstacleWidth + 10;
const int Segment = 6;

int menuIndex = 0;
int selectedMenuIndex = 0;
enum Menu {
    SCREENHOME,
    SCREENABOUT,
    SCREENEXIT,
    SCREENGAME
};

void resetObstacle(Obstacle* obstacle, ObstacleConfig config)
{
    obstacle->top.height = (float)GetRandomValue((int)config.gapHeight / 2, (int)config.obstacleHeight - ((int)config.gapHeight * 2));
    obstacle->top.width = ObstacleWidth;
    obstacle->top.x = config.startX;
    obstacle->top.y = (float)ObstacleTopY;

    obstacle->bottom.height = config.obstacleHeight - obstacle->top.height - config.gapHeight;
    obstacle->bottom.width = ObstacleWidth;
    obstacle->bottom.x = config.startX;
    obstacle->bottom.y = config.obstacleHeight - obstacle->bottom.height;
}
void initGame()
{
    InitWindow(ScreenWidth, ScreenHeight, PROJECT_NAME);
    SetTargetFPS(FpsValue);
    bird.pos.x = BirdInitialX;
    bird.pos.y = BirdInitialY;
    bird.speedY = 0;
    for (int i = 0; i < NUMOBSTACLES; i++) {
        ObstacleConfig config = { (float)ScreenWidth + ((float)i * (ObstacleWidth + ObstacleSpacing)), (float)ScreenHeight, ObstacleGap };
        resetObstacle(&obstacles[i], config);
    }
}

void handleHome()
{
    const char* menuOptions[] = { "Start Game", "About", "Exit" };
    const int MenuOptionsNumber = sizeof(menuOptions) / sizeof(menuOptions[0]);
    const int MenuFontSize = 20;
    const int MenuVerticalSpace = 40;
    const int MenuInitialY = 175;
    if (IsKeyPressed(KEY_UP)) {
        menuIndex--;
        if (menuIndex < 0) {
            menuIndex = MenuOptionsNumber - 1;
        }
    }
    if (IsKeyPressed(KEY_DOWN)) {
        menuIndex++;
        if (menuIndex == MenuOptionsNumber) {
            menuIndex = 0;
        }
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
        Color_t color = (i == menuIndex) ? YELLOW : DARKGRAY;
        DrawText(menuOptions[i], (ScreenWidth / 2) - (MeasureText(menuOptions[i], MenuFontSize) / 2), MenuInitialY + (i * MenuVerticalSpace), MenuFontSize, color);
    }
}

void handleAbout()
{
    const int DevelopersTextPosX = 250;
    const int DevelopersTextPosY = 50;
    const int DevelopersTextFontSize = 50;
    const int DevelopersPosX = 225;
    const int DevelopersPosY = 115;
    const int DevelopersFontSize = 30;
    const int VersionTextPosX = 250;
    const int VersionTextPosY = 230;
    const int VersionTextFontSize = 50;
    const int VersionPosX = 240;
    const int VersionPosY = 295;
    const int VersionFontSize = 30;
    DrawText("DEVELOPERS\0}", DevelopersTextPosX, DevelopersTextPosY, DevelopersTextFontSize, DARKBLUE);
    DrawText("Abdulkerim ELMAS\nEnes GURDEN\0}", DevelopersPosX, DevelopersPosY, DevelopersFontSize, LIGHTGRAY);
    DrawText("VERSION\0}", VersionTextPosX, VersionTextPosY, VersionTextFontSize, DARKBLUE);
    DrawText("1.0.0\0}", VersionPosX, VersionPosY, VersionFontSize, LIGHTGRAY);
    if (IsKeyPressed(KEY_BACKSPACE)) {
        selectedMenuIndex = SCREENHOME;
    }
}

void gameLoop(Texture2D birdTex)
{
    if (IsKeyPressed(KEY_UP)) {
        bird.speedY = -sqrtf(Gravity * MaxHeight);
    }

    bird.pos.y = bird.pos.y + bird.speedY * deltaT;
    bird.speedY = bird.speedY + Gravity * deltaT;

    for (int i = 0; i < NUMOBSTACLES; i++) {
        obstacles[i].top.x -= ObstacleSpeed;
        obstacles[i].bottom.x -= ObstacleSpeed;
        if (obstacles[i].top.x == -obstacles[i].top.width) {
            ObstacleConfig config = { (float)ScreenWidth, (float)ScreenHeight, ObstacleGap };
            resetObstacle(&obstacles[i], config);
        }
        if (obstacles[i].top.x + ObstacleWidth == bird.pos.x) {
            score++;
        }
        snprintf(scoreText, sizeof(scoreText), "Score \n\t %d", score); // NOLINT
    }

    Vector2 birdCenter = { .x = bird.pos.x + ((float)birdTex.width / Half), .y = bird.pos.y + ((float)birdTex.height / Half) };
    for (int i = 0; i < NUMOBSTACLES; i++) {
        if ((bird.pos.y > (float)ScreenHeight) || (bird.pos.y < (float)-birdTex.height && bird.pos.x > obstacles[i].top.x) || CheckCollisionCircleRec(birdCenter, (float)birdTex.height / Half, obstacles[i].top) || CheckCollisionCircleRec(birdCenter, (float)birdTex.height / Half, obstacles[i].bottom)) {
            bird.pos.x = BirdInitialX;
            bird.pos.y = BirdInitialY;
            for (int j = 0; j < NUMOBSTACLES; j++) {
                ObstacleConfig config = { (float)ScreenWidth + ((float)j * (ObstacleWidth + ObstacleSpacing)), (float)ScreenHeight, ObstacleGap };
                resetObstacle(&obstacles[j], config);
            }
            score = 0;
            bird.speedY = 0;
        }
    }

    for (int i = 0; i < NUMOBSTACLES; i++) {
        DrawRectangleRec(obstacles[i].top, GREEN);
        DrawRectangleRec(obstacles[i].bottom, GREEN);

        Rectangle borderRoundedTop = {
            .x = obstacles[i].top.x - ((RoundedWidth - ObstacleWidth) / Half),
            .y = obstacles[i].top.height - RoundedHeight,
            .width = RoundedWidth,
            .height = RoundedHeight,
        };
        DrawRectangleRounded(borderRoundedTop, ThicknessRound, Segment, GREEN);
        DrawRectangleRoundedLinesEx(borderRoundedTop, ThicknessRound, Segment, ThicknessLine, DARKGRAY);
        DrawLine((int)obstacles[i].top.x, (int)obstacles[i].top.y, (int)obstacles[i].top.x, (int)obstacles[i].top.height - (int)borderRoundedTop.height, BLACK);
        DrawLine((int)obstacles[i].top.x + (int)ObstacleWidth, (int)obstacles[i].top.y, (int)obstacles[i].top.x + (int)ObstacleWidth, (int)obstacles[i].top.height - (int)borderRoundedTop.height, BLACK);
        Rectangle borderRoundedBottom = {
            .x = obstacles[i].bottom.x - ((RoundedWidth - ObstacleWidth) / Half),
            .y = obstacles[i].bottom.y,
            .width = RoundedWidth,
            .height = RoundedHeight
        };
        DrawRectangleRounded(borderRoundedBottom, ThicknessRound, Segment, GREEN);
        DrawRectangleRoundedLinesEx(borderRoundedBottom, ThicknessRound, Segment, ThicknessLine, DARKGRAY);
        DrawLine((int)obstacles[i].bottom.x, (int)obstacles[i].bottom.y + (int)borderRoundedBottom.height, (int)obstacles[i].bottom.x, ScreenHeight, BLACK);
        DrawLine((int)obstacles[i].bottom.x + (int)ObstacleWidth, (int)obstacles[i].bottom.y + (int)borderRoundedBottom.height, (int)obstacles[i].bottom.x + (int)ObstacleWidth, ScreenHeight, BLACK);
    }
    DrawTexture(birdTex, (int)bird.pos.x, (int)bird.pos.y, WHITE);
    const int ScorePosX = 350;
    const int ScorePosY = 50;
    const int ScoreFontSize = 50;
    DrawText(scoreText, ScorePosX, ScorePosY, ScoreFontSize, LIGHTGRAY);
}

void windowLoop(Texture2D birdTex)
{

    switch (selectedMenuIndex) {
    case SCREENHOME:
        handleHome();
        break;
    case SCREENABOUT: {
        handleAbout();
    } break;
    case SCREENEXIT:
        CloseWindow(); // ask senior WARNING: GLFW: Error: 65537 Description: The GLFW library is not initialized
        break;
    case SCREENGAME:
        gameLoop(birdTex);
        break;
    default:
        break;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        menuIndex = SCREENHOME;
        selectedMenuIndex = SCREENHOME;
    }
}

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    initGame();
    Texture2D birdTex = LoadTexture("bird.png");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);

        windowLoop(birdTex);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
