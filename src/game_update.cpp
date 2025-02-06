#include "game.hpp"

void Game::create_current_scene()
{
    switch (current_scene)
    {
    case SceneID::Main:
        scene = new MainScene(window, assets);
        break;
    }
}

void Game::update_scene()
{
    if (scene != nullptr)
    {
        SceneID scene_result = scene->run();

        if (scene_result != current_scene)
        {
            current_scene = scene_result;
            delete scene;
            scene = nullptr;
            create_current_scene();
        }
    }
    else
    {
        create_current_scene();
    }
}