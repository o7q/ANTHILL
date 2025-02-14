#pragma once

#include "../scene/scene.hpp"

#include "../player/player.hpp"
#include "../world/world.hpp"

#include "../engine/texture/texture.hpp"

class MainScene : public Scene
{
public:
    MainScene(Window &window, Assets &assets) : Scene(window, assets),
                                                m_player(window, m_world_partitons),
                                                m_camera(window.getScale(), window.getScale())
    {
        m_player.setPosition(0, -50);
        m_player.setBoundsSize(8, 25);

        m_world_partitons.push_back(new World(window.getSDLRenderer(), 1000, 1000));
        m_world_partitons.push_back(new World(window.getSDLRenderer(), 1000, 1000));

        m_world_partitons[1]->move(0, 1000);

        World::Portal portal1{m_world_partitons[1], false, true, false, false};
        World::Portal portal2{m_world_partitons[0], true, false, false, false};

        m_world_partitons[0]->setPortal(portal1);
        m_world_partitons[1]->setPortal(portal2);

        crosshair_texture = new Texture(window.getSDLRenderer(), assets.images.crosshair_1x.getSDLSurface());
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

        if (crosshair_texture != nullptr)
        {
            delete crosshair_texture;
        }
    }
    SceneID run() override;

private:
    void handle_world();
    void handle_update();
    void handle_render();
    void handle_input();
    void handle_hud();

    int max_level = 0;
    bool played_past_start = false;

private:
    void delete_world(World *world)
    {
        if (world != nullptr)
        {
            delete world;
            world = nullptr;
        }
    }

private:
    Player m_player;
    Camera m_camera;
    std::vector<World *> m_world_partitons;
    Particle::Preset m_preset;
    BoundingBox m_update_bb;
    Texture *crosshair_texture = nullptr;

    Vec2<float> aim_position;
};