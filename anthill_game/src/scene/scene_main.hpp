#pragma once

#include "scene.hpp"
#include "../player/player.hpp"
#include "../world/world.hpp"

class MainScene : public Scene
{
public:
    MainScene(Window &window, Assets &assets) : Scene(window, assets),
                                                world(window.getSDLRenderer(), 256, 256),
                                                player(window, world)
    {
        player.setPosition(20, 20);
        player.setBoundsSize(8, 25);
    }

    SceneID run() override;

private:
    World world;
    Player player;
    Particle::Preset preset;
    Camera camera;
};