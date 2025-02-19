#pragma once

#include "../engine/texture/texture.hpp"
#include "../scene/scene.hpp"
#include "../player/player.hpp"

#include "../world/world.hpp"
#include "../world_manager/world_manager.hpp"

#include "../bullet/bullet.hpp"
#include "../bullet_manager/bullet_manager.hpp"

class MainScene : public Scene
{
public:
    MainScene(Window &window, Assets &assets) : Scene(window, assets),
                                                m_world_manager(window),
                                                m_player(window, m_world_manager.getWorlds()),
                                                m_camera(window.getScale(), window.getScale())
    {
        m_player.setPosition(0, -50);
        m_player.setBoundsSize(8, 25);

        m_bullet_manager.setWorldManager(&m_world_manager);

        m_world_manager.queue(WorldGenerator::Settings(2000, 2000, -1, WorldGenerator::Settings::Preset::Jungle));

        crosshair_texture = new Texture(m_window.getSDLRenderer(), m_assets.surfaces.crosshair_1x);
    }
    ~MainScene() override
    {
        if (crosshair_texture != nullptr)
        {
            delete crosshair_texture;
        }
    }
    SceneID run() override;

private:
    void update_player();
    void update_world();
    void update_entities();

    void update_render();
    void update_input();
    void update_hud();

private:
    WorldManager m_world_manager;
    BulletManager m_bullet_manager;
    Player m_player;
    Camera m_camera;

    BoundingBox m_world_update_bb;

    Vec2<float> m_aim_position_gamepad;

    Texture *crosshair_texture = nullptr;
};