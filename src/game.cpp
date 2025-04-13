#include "game.h"

#include <raylib.h>

Game::Game()
    : m_name("Blappy Fird")
    , m_fps(60)
    , m_score(0)
    , m_screenDimension({ 900, 450 })
    , m_obstacleCount(5)
    , m_obstacleGap(150.0f)
    , m_gameSpeed(2.5f)
    , m_gravity(1400.0f)
    , m_painter({ 900, 450 })
    , m_controller()
{
}

Game::~Game()
{
}

bool Controller::isUpPressed()
{
    IsKeyPressed(KEY_UP);
    return false;
}

bool Controller::isDownPressed()
{
    IsKeyPressed(KEY_DOWN);
    return false;
}

bool Controller::isBackPressed()
{
    IsKeyPressed(KEY_BACKSPACE);
    return false;
}

bool Controller::isEnterPressed()
{
    IsKeyPressed(KEY_ENTER);
    return false;
}

bool Controller::isEscPressed()
{
    IsKeyPressed(KEY_ESCAPE);
    return false;
}

bool Controller::isLeftMousePressed()
{
    IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    return false;
}

bool Controller::isRightMousePressed()
{
    IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
    return false;
}

void Painter::drawText(Text text)
{
    DrawText(text.text.c_str(), text.pos.x, text.pos.y, text.fontSize, GetColor(text.color.rgba));
}

void Painter::drawRect(Rectangle_s rect)
{
    Rectangle rectangle = {
        .x = rect.m_pos.x,
        .y = rect.m_pos.y,
        .width = rect.width,
        .height = rect.height,
    };
    DrawRectangleRec(rectangle, GetColor(rect.color.rgba));
}

void Painter::drawLine(Line line)
{
    DrawLine(line.start.x, line.start.y, line.end.x, line.end.y, GetColor(line.color.rgba));
}

void Painter::drawCircle(Circle circle)
{
    int centerX = circle.pos.x;
    int centerY = circle.pos.y;
    DrawCircle(centerX, centerY, circle.radius, GetColor(circle.color.rgba));
}

float Painter::sceneWidth()
{
    return m_sceneWidth;
}
float Painter::sceneHeight()
{
    return m_sceneHeight;
}

void Game::init()
{
    InitWindow(m_screenDimension.first, m_screenDimension.second, m_name.c_str());
    SetTargetFPS(m_fps);

    Bird* bird = new Bird();
    bird->m_pos.x = m_screenDimension.first / 5.0f;
    bird->m_pos.y = m_screenDimension.second / 2.0f;
    m_gameObjects.push_back(bird);
    m_gameObjects.push_back(new Obstacle(100.0, { 100, 200 }));
    m_gameObjects.push_back(new Obstacle(100.0, { 400, 300 }));
    m_gameObjects.push_back(new Obstacle(100.0, { 700, 400 }));
};

void Game::loop()
{
    for (auto gameObject : m_gameObjects) {
        gameObject->update();
    }
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(SKYBLUE);
    for (auto gameObject : m_gameObjects) {
        gameObject->draw(m_painter);
    }

    EndDrawing();
}

bool Game::shouldClose()
{
    return WindowShouldClose();
}
