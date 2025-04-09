#include "game.h"
#include <cmath>
#include <cstdio>
#include <raylib.h>

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    Game game;
    game.init();

    while (!game.shouldClose()) {
        game.loop();
        game.draw();
        WaitTime(0.5);
    }

    return 0;
}