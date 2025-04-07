#pragma once

#include <list>
#include <math.h>
#include <string>

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
    Point(float x_, float y_)
        : x(x_)
        , y(y_)
    {
    }
    Point()
        : x(0.0f)
        , y(0.0f)
    {
    }
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
    Painter(int sceneWidth, int sceneHeight)
        : m_sceneHeight(sceneHeight)
        , m_sceneWidth(sceneWidth)
    {
    }

    void drawText(Text text);
    void drawRect(Rectangle_s rect);
    void drawLine(Line line);
    void drawCircle(Circle circle);
    float sceneWidth();
    float sceneHeight();

private:
    int m_sceneWidth;
    int m_sceneHeight;
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
    {
    }

    void draw(Painter painter) override
    {
    }
    void update() override
    {
    }
};

class Bird : public GameObject {
private:
public:
    Point m_pos;
    float m_speed;
    Bird()
        : m_pos()
        , m_speed()
    {
    }

    void draw(Painter painter) override
    {
        const float radius = 18.0f;
        Circle circle { m_pos, radius, C_YELLOW };
        painter.drawCircle(circle);
    }
    void update() override
    {
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
    int m_obstacleCount;
    float m_obstacleGap;
    float m_gameSpeed;

    std::list<GameObject*> m_gameObjects;
    Controller m_controller;

public:
    Game();
    ~Game();

    std::pair<int, int> m_screenDimension;
    std::string m_name;
    float m_gravity;
    Painter m_painter;

    void init();
    void loop();
    void draw();

    bool shouldClose();
};
