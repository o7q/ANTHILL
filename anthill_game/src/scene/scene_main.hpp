#pragma once

#include "scene.hpp"
#include "../player/player.hpp"
#include "../world/world.hpp"

class MainScene : public Scene
{
public:
    MainScene(Window &window, Assets &assets) : Scene(window, assets),
                                                m_player(window, m_world_partitons),
                                                m_camera(window.getScale(), window.getScale())
    {

        m_player.setPosition(0, -50);
        m_player.setBoundsSize(8, 25);

        m_world_partitons.push_back(new World(window.getSDLRenderer(), 220, 100));
        m_world_partitons.push_back(new World(window.getSDLRenderer(), 220, 100));

        m_world_partitons[1]->move(-200, 0);

        m_world_partitons[0]->setPortal(m_world_partitons[1], 0);
        m_world_partitons[1]->setPortal(m_world_partitons[0], 1);
    }
    ~MainScene() override
    {
        for (World *world_partition : m_world_partitons)
        {
            if (world_partition != nullptr)
            {
                delete world_partition;
            }
        }
    }

    SceneID run() override;

private:
    Player m_player;
    Camera m_camera;
    std::vector<World *> m_world_partitons;
    Particle::Preset m_preset;
};