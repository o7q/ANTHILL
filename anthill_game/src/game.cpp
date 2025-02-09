#include "game.hpp"

#include "math/random.hpp"

Game::Game() : window("ANTHILL", 512, 512, 384)
{
    Random::seed();
    window.time().setTargetFramerate(144);

    while (window.isOpen())
    {
        window.time().frameStart();
        window.update();

        window.clear();
        update_scene();
        window.display();

        window.time().frameEnd();
        window.time().delay();
    }

    if (scene != nullptr)
    {
        delete scene;
    }
}