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

typedef struct {
    int startX;
    int screenHeight;
    float gapHeight;
} ObstacleConfig;

const float Half = 2.0F;
const int ScreenWidth = 900;
const int ScreenHeight = 450;
const int FpsValue = 60;

const int BirdInitialX = 300;
const int BirdInitialY = 225;
Bird bird;

int score = 0;
enum {
    NUMOBSTACLES = 4,
    SCOREBUFFERCOUNT = 21,
};
char scoreText[SCOREBUFFERCOUNT];

const int ObstacleTopY = 0;
const int ObstacleWidth = 100;
const int ObstacleGap = 150;
const int ObstacleSpacing = 150;
const float ObstacleSpeed = 2.5;
Obstacle obstacles[NUMOBSTACLES];

const float MaxHeight = ObstacleWidth + (ObstacleSpacing / Half);
const float MaxHeightTime = 0.5;
const float Gravity = 2 * MaxHeight / MaxHeightTime / MaxHeightTime;
float deltaT = 1.0 / (float)FpsValue;

const float ThicknessRound = 0.5;
const float ThicknessLine = 0.3;
const int RoundedHeight = 20;
const int RoundedWidth = ObstacleWidth + 10;
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
    obstacle->top.height = GetRandomValue(config.gapHeight / 2, (float)config.screenHeight - (config.gapHeight * 2));
    obstacle->top.width = ObstacleWidth;
    obstacle->top.x = config.startX;
    obstacle->top.y = ObstacleTopY;

    obstacle->bottom.height = config.screenHeight - obstacle->top.height - config.gapHeight;
    obstacle->bottom.width = ObstacleWidth;
    obstacle->bottom.x = config.startX;
    obstacle->bottom.y = config.screenHeight - obstacle->bottom.height;
}
void initGame()
{
    InitWindow(ScreenWidth, ScreenHeight, PROJECT_NAME);
    SetTargetFPS(FpsValue);
    bird.pos.x = BirdInitialX;
    bird.pos.y = BirdInitialY;
    bird.speedY = 0;
    for (int i = 0; i < NUMOBSTACLES; i++) {
        ObstacleConfig config = { ScreenWidth + (i * (ObstacleWidth + ObstacleSpacing)), ScreenHeight, ObstacleGap };
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
        Color color = (i == menuIndex) ? YELLOW : DARKGRAY;
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
            ObstacleConfig config = { ScreenWidth, ScreenHeight, ObstacleGap };
            resetObstacle(&obstacles[i], config);
        }
        if (obstacles[i].top.x + ObstacleWidth == bird.pos.x) {
            score++;
        }
        snprintf(scoreText, sizeof(scoreText), "Score \n\t %d", score); // NOLINT
    }

    Vector2 birdCenter = { .x = bird.pos.x + (birdTex.width / Half), .y = bird.pos.y + (birdTex.height / Half) };
    for (int i = 0; i < NUMOBSTACLES; i++) {
        if ((bird.pos.y > ScreenHeight) || CheckCollisionCircleRec(birdCenter, birdTex.height / Half, obstacles[i].top) || CheckCollisionCircleRec(birdCenter, birdTex.height / Half, obstacles[i].bottom)) {
            bird.pos.x = BirdInitialX;
            bird.pos.y = BirdInitialY;
            for (int j = 0; j < NUMOBSTACLES; j++) {
                ObstacleConfig config = { ScreenWidth + (j * (ObstacleWidth + ObstacleSpacing)), ScreenHeight, ObstacleGap };
                resetObstacle(&obstacles[j], config);
            }
            score = 0;
            bird.speedY = 0;
        }
    }

    for (int i = 0; i < NUMOBSTACLES; i++) {
        DrawRectangleRec(obstacles[i].top, GREEN);
        DrawRectangleRec(obstacles[i].bottom, GREEN);

        Rectangle borderRoundedTop = { .height = RoundedHeight, .width = RoundedWidth, .x = obstacles[i].top.x - ((RoundedWidth - ObstacleWidth) / Half), .y = obstacles[i].top.height - RoundedHeight };
        DrawRectangleRounded(borderRoundedTop, ThicknessRound, Segment, GREEN);
        DrawRectangleRoundedLinesEx(borderRoundedTop, ThicknessRound, Segment, ThicknessLine, DARKGRAY);
        DrawLine(obstacles[i].top.x, obstacles[i].top.y, obstacles[i].top.x, obstacles[i].top.height - borderRoundedTop.height, BLACK);
        DrawLine(obstacles[i].top.x + ObstacleWidth, obstacles[i].top.y, obstacles[i].top.x + ObstacleWidth, obstacles[i].top.height - borderRoundedTop.height, BLACK);
        Rectangle borderRoundedBottom = { .height = RoundedHeight, .width = RoundedWidth, .x = obstacles[i].bottom.x - ((RoundedWidth - ObstacleWidth) / Half), .y = obstacles[i].bottom.y };
        DrawRectangleRounded(borderRoundedBottom, ThicknessRound, Segment, GREEN);
        DrawRectangleRoundedLinesEx(borderRoundedBottom, ThicknessRound, Segment, ThicknessLine, DARKGRAY);
        DrawLine(obstacles[i].bottom.x, obstacles[i].bottom.y + borderRoundedBottom.height, obstacles[i].bottom.x, ScreenHeight, BLACK);
        DrawLine(obstacles[i].bottom.x + ObstacleWidth, obstacles[i].bottom.y + borderRoundedBottom.height, obstacles[i].bottom.x + ObstacleWidth, ScreenHeight, BLACK);
    }
    DrawTexture(birdTex, bird.pos.x, bird.pos.y, WHITE);
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
