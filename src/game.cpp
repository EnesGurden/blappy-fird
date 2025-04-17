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
    return IsKeyPressed(KEY_UP);
}

bool Controller::isDownPressed()
{
    return IsKeyPressed(KEY_DOWN);
}

bool Controller::isBackPressed()
{
    return IsKeyPressed(KEY_BACKSPACE);
}

bool Controller::isEnterPressed()
{
    return IsKeyPressed(KEY_ENTER);
}

bool Controller::isEscPressed()
{
    return IsKeyPressed(KEY_ESCAPE);
}

bool Controller::isLeftMousePressed()
{
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool Controller::isRightMousePressed()
{
    return IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
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

void Game::initObjects()
{
    Bird* bird = new Bird();
    bird->m_pos.x = m_screenDimension.first / 5.0f;
    bird->m_pos.y = m_screenDimension.second / 2.0f;
    m_gameObjects.push_back(bird);
    m_gameObjects.push_back(new Obstacle(100.0, { m_screenDimension.first + 2.6, 200 }));
}

void Game::init()
{
    InitWindow(m_screenDimension.first, m_screenDimension.second, m_name.c_str());
    SetTargetFPS(m_fps);
    initObjects();
}

void Game::checkCollision()
{
    auto iter = m_gameObjects.begin();
    auto* bird = (Bird*)*iter;
    iter++;
    Vector2 center = { bird->m_pos.x, bird->m_pos.y };
    Obstacle* obstacle = (Obstacle*)*iter;
    if (obstacle->getPos().x < -obstacle->getWidth()) {
        m_gameObjects.erase(iter);
        return;
    }

    Rectangle upperRec = {
        obstacle->upperRectangle().m_pos.x,
        obstacle->upperRectangle().m_pos.y,
        obstacle->upperRectangle().width,
        obstacle->upperRectangle().height
    };
    Rectangle bottomRec = {
        obstacle->bottomRectangle(m_screenDimension.second).m_pos.x,
        obstacle->bottomRectangle(m_screenDimension.second).m_pos.y,
        obstacle->bottomRectangle(m_screenDimension.second).width,
        obstacle->bottomRectangle(m_screenDimension.second).height
    };

    const bool BirdOutScreen = bird->m_pos.y > m_screenDimension.second || (bird->m_pos.y < 0 && bird->m_pos.x > obstacle->getPos().x);
    const bool CollisionUp = CheckCollisionCircleRec(center, bird->radius, upperRec);
    const bool CollisionBottom = CheckCollisionCircleRec(center, bird->radius, bottomRec);

    if (BirdOutScreen || CollisionUp || CollisionBottom) {
        m_gameObjects.clear();
        initObjects();
    }
};

void Game::loop()
{
    for (auto gameObject : m_gameObjects) {
        gameObject->update(m_controller);
    }
    Game::checkCollision();
}

void Game::draw()
{
    BeginDrawing();
    ClearBackground(SKYBLUE);

    if (!m_gameObjects.empty()) {
        GameObject* lastObject = m_gameObjects.back();
        if (auto* obstacle = dynamic_cast<Obstacle*>(lastObject)) {
            if (obstacle->getPos().x >= m_screenDimension.first && obstacle->getPos().x <= m_screenDimension.first + 2.5) {
                float posY = rand() % (m_screenDimension.second - 200) + 100;
                m_gameObjects.push_back(new Obstacle(100.0, { m_screenDimension.first + 250, posY }));
            }
        }
    }

    for (auto gameObject : m_gameObjects) {
        gameObject->draw(m_painter);
    }

    EndDrawing();
}

bool Game::shouldClose()
{
    return WindowShouldClose();
}
