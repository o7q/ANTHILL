#include "scene_main.hpp"

#include "../engine/logger/logger.hpp"

SceneID MainScene::run()
{
    if (init())
    {
        Log::log(Log::Type::Info, "MainScene", "Init");
        m_window.setCursor(m_assets.images.crosshair_2x.getSDLSurface());
    }

    if (update())
    {
        update_input();

        update_world();
        update_entities();
        update_player();
        m_bullet_manager.update(m_world_update_bb, DT);

        for (const Bullet &bullet : m_bullet_manager.getHitBullets())
        {
            World *hit_world = bullet.getHitWorld();
            if (hit_world != nullptr)
            {
                Vec2<float> bullet_pos = bullet.getPosition();
                hit_world->drawParticles(bullet_pos.x, bullet_pos.y, bullet.getPower(), Particle());
            }
        }

        update_render();
        update_hud();
    }

    return SceneID::Main;
}