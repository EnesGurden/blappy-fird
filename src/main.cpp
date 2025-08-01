#include "game.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    Game game;
    game.init();

    while (!game.shouldClose()) {
        game.loop();
        game.draw();
    }

    return 0;
}