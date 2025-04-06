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

    while (true) {
        game.loop();
        printf("\r\nI am here");
        game.draw();
    }

    return 0;
}