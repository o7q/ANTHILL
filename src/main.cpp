#include "game.hpp"

int main()
{
    px::Vec2u windowSize   = {1280, 720};
    px::Vec2u aspect       = {4, 3};
    unsigned int scale = 70;

    px::Vec2u renderSize = aspect * scale;
    Game game(windowSize, renderSize);

    return 0;
}
