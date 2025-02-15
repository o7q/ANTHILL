#pragma once

#include "../scene/scene.hpp"

#include "../player/player.hpp"
#include "../world/world.hpp"

#include "../engine/texture/texture.hpp"

#include "world_partitons/wp_manager.hpp"

class MainScene : public Scene
{
public:
    MainScene(Window &window, Assets &assets) : Scene(window, assets),
                                                m_wp_manager(window, 1000, 1000),
                                                m_player(window, m_wp_manager.getWorldPartitions()),
                                                m_camera(window.getScale(), window.getScale())
    {
        m_player.setPosition(0, -50);
        m_player.setBoundsSize(8, 25);

        crosshair_texture = new Texture(window.getSDLRenderer(), assets.images.crosshair_1x.getSDLSurface());
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
    void handle_update();
    void handle_render();
    void handle_input();
    void handle_hud();

private:
    WPManager m_wp_manager;
    Player m_player;
    Camera m_camera;

    BoundingBox m_world_update_bb;

    Particle::Preset m_preset;

    Texture *crosshair_texture = nullptr;

    Vec2<float> m_aim_position;
    Vec2<float> m_aim_position_gamepad;
};