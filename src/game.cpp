#include "game.hpp"

#include "math/random.hpp"
#include "scene/scene_main.hpp"

Game::Game() : window("ANTHILL", 512, 512, 256)
{
    Random::seed();
    window.time().setTargetFramerate(60);

    scene = new MainScene(window);

    while (window.isOpen())
    {
        window.time().frameStart();

        window.update();

        window.clear();
        update();
        scene->run();
        window.display();

        window.time().frameEnd();
        window.time().delay();
    }

    if (scene != nullptr)
    {
        delete scene;
    }
}