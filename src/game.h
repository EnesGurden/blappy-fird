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
    virtual void update(Controller controller) = 0;
};

class Score : public GameObject {
    Point pos;
    int value;

    void draw(Painter painter) override
    {
        Text text(value, pos, C_RED);
        painter.drawText(text);
    }

    void update(Controller controller) override
    {
    }
};

class Obstacle : public GameObject {
public:
    Obstacle(float width, Point pos)
        : m_width(width)
        , m_pos(pos)
    {
    }

    void draw(Painter painter) override
    {
        painter.drawRect(upperRectangle());
        painter.drawRect(bottomRectangle(painter.sceneHeight()));
    }
    void update(Controller controller) override
    {
        m_pos.x -= 2.5f;
    }

    Rectangle_s upperRectangle()
    {
        float upperRectHeight = m_pos.y - 150.0f / 2.0f;
        Rectangle_s upper = { m_pos, m_width, upperRectHeight, C_GREEN };
        upper.m_pos.y -= 150.0f / 2.0f + upperRectHeight;
        return upper;
    }

    Rectangle_s bottomRectangle(float sceneHeight)
    {
        float upperRectHeight = m_pos.y - 150.0f / 2.0f;
        float bottomRectHeight = sceneHeight - upperRectHeight - 150.0f;
        Rectangle_s bottom = { m_pos, m_width, bottomRectHeight, C_GREEN };
        bottom.m_pos.y += 150.0f / 2.0f;
        return bottom;
    }

    Point getPos()
    {
        return m_pos;
    }

    float getWidth()
    {
        return m_width;
    }

private:
    Point m_pos;
    float m_width;
};

class Bird : public GameObject {
private:
public:
    Point m_pos;
    float m_speed;
    float radius;
    Bird()
        : m_pos()
        , m_speed()
        , radius(18.0f)
    {
    }

    void draw(Painter painter) override
    {
        Circle circle { m_pos, radius, C_YELLOW };
        painter.drawCircle(circle);
    }

    void update(Controller controller) override
    {
        if (controller.isLeftMousePressed() || controller.isUpPressed()) {
            m_speed = 494.97;
        }

        m_pos.y -= m_speed * (1.0 / 60);
        m_speed -= 23.33;
    }
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

    void initObjects();
    void init();
    void checkCollision();
    void loop();
    void draw();

    bool shouldClose();
};
