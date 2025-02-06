#pragma once

#include "scene.hpp"
#include "../entity/entity.hpp"
#include "../world/world.hpp"

class MainScene : public Scene
{
public:
    MainScene(Window &window) : Scene(window), world(window.getSDLRenderer(), 256, 256)
    {
        player.setPosition(20, 20);
        player.setSize(20, 30);
    }

    void run() override;

private:
    Entity player;
    Particle::Preset preset;
    World world;
    Camera camera;
};