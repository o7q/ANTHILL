#pragma once

#include "scene.hpp"
#include "../player/player.hpp"
#include "../world/world.hpp"

class MainScene : public Scene
{
public:
    MainScene(Window &window, Assets &assets) : Scene(window, assets),
                                                world(window.getSDLRenderer(), 512, 512),
                                                player(window, world),
                                                camera(window.getScale(), window.getScale())
    {
        player.setPosition(20, -50);
        player.setBoundsSize(8, 25);
    }

    SceneID run() override;

private:
    World world;
    Player player;
    Camera camera;
    Particle::Preset preset;
};