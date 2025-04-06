#pragma once

#include <list>
#include <math.h>
#include <string>
#include <tuple>

enum COLOR {
    C_RED = 0xFF0000FF,
    C_GREEN = 0x00FF00FF,
    C_BLUE = 0x0000FFFF,
    C_WHITE = 0xFFFFFFFF,
    C_BLACK = 0x000000FF,
    C_YELLOW = 0xFFFF00FF,
};

struct Color_t {
    unsigned long rgba;

    // Allow implicit conversion from unsigned long (for raw values)
    Color_t(unsigned long val = 0)
        : rgba(val)
    {
    }

    // Allow implicit conversion from COLOR enum
    Color_t(COLOR col)
        : rgba(static_cast<unsigned long>(col))
    {
    }
};

struct Point {
    float x;
    float y;
};

struct Text {
    std::string text;
    Point pos;
    float fontSize;
    Color_t color;

    Text(int value, Point pos, Color_t color);
};

struct Rectangle_s {
    Point m_pos;
    float width;
    float height;
    Color_t color;
};

struct Line {
    Point start;
    Point end;
    float width;
    Color_t color;
};

struct Circle {
    Point pos;
    float radius;
    Color_t color;
};

class Painter {
public:
    void drawText(Text text);
    void drawRect(Rectangle_s rect);
    void drawLine(Line line);
    void drawCircle(Circle circle);
    float sceneWidth();
    float sceneHeight();
};
struct GameObject {
    virtual void draw(Painter painter) = 0;
    virtual void update() = 0;
};

class Score : public GameObject {
    Point pos;
    int value;

    void draw(Painter painter) override
    {
        Text text(value, pos, C_RED);
        painter.drawText(text);
    }

    void update() override
    {
        printf("\r\nThis is Score update");
    }
};

class Obstacle : public GameObject {
    float m_width;
    float m_gap;
    Point m_pos;

public:
    Obstacle()
        : m_width(100.0f)
        , m_gap(150.0f)
        , m_pos()
    // , m_pos({ m_painter.scenewidth(), m_painter.sceneHeight() / 2.0f })
    {
    }

    void draw(Painter painter) override
    {
        float upperRectHeight = m_pos.y - m_gap / 2;
        float bottomRectHeight = painter.sceneHeight() - upperRectHeight - m_gap;
        Rectangle_s upper { m_pos, m_width, upperRectHeight, C_GREEN };
        Rectangle_s bottom { m_pos, m_width, bottomRectHeight, C_GREEN };
        painter.drawRect(upper);
        painter.drawRect(bottom);
    }
    void update() override
    {
        printf("\r\nThis is Obstacle update");
    }
};

class Bird : public GameObject {
private:
    Point m_pos;
    float m_speed;

public:
    Bird()
        // : m_pos({ Game::m_painter.scenewidth() / 3.0f, Game::m_painter.sceneHeight() / 2.0f })
        : m_pos()
        , m_speed()
    {
    }

    void draw(Painter painter) override
    {
        Circle circle { m_pos, 30.0f };
        painter.drawCircle(circle);
    }
    void update() override
    {
        printf("\r\nThis is Bird update");
    }
};

class Controller {
public:
    bool isUpPressed();
    bool isDownPressed();
    bool isBackPressed();
    bool isEnterPressed();
    bool isEscPressed();
    bool isLeftMousePressed();
    bool isRightMousePressed();
};

class Game {
private:
    int m_fps;
    int m_score;
    std::tuple<int, int> m_screenDimension;
    int m_obstacleCount;
    float m_obstacleGap;
    float m_gameSpeed;

    std::list<GameObject*> m_gameObjects;
    Controller m_controller;

public:
    Game();
    ~Game();

    std::string m_name;
    float m_gravity;
    Painter m_painter;

    void init();
    void loop();
    void draw();
};
