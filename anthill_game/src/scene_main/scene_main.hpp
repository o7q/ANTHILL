#pragma once

#include "../scene/scene.hpp"

#include "../player/player.hpp"
#include "../world/world.hpp"

#include "../engine/texture/texture.hpp"

#include "world_partitons/wp_manager.hpp"
#include "bullets/bullet_manager.hpp"

#include "../bullet/bullet.hpp"

class MainScene : public Scene
{
public:
    MainScene(Window &window, Assets &assets) : Scene(window, assets),
                                                m_wp_manager(window, 1000, 1000),
                                                m_bullet_manager(m_wp_manager, m_world_update_bb),
                                                m_player(window, m_wp_manager.getWorldPartitions()),
                                                m_camera(window.getScale(), window.getScale())
    {
        m_player.setPosition(0, -50);
        m_player.setBoundsSize(8, 25);

        crosshair_texture = new Texture(m_window.getSDLRenderer(), m_assets.images.crosshair_1x.getSDLSurface());
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
    WPManager m_wp_manager;
    BulletManager m_bullet_manager;
    Player m_player;
    Camera m_camera;

    BoundingBox m_world_update_bb;

    Vec2<float> m_aim_position;
    Vec2<float> m_aim_position_gamepad;

    Texture *crosshair_texture = nullptr;
};