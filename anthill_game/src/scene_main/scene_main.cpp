#include "scene_main.hpp"

#include "../engine/logger/logger.hpp"

SceneID MainScene::run()
{
    if (init())
    {
        Log::log(Log::Level::Info, "MainScene", "Init");
        m_window.setCursor(m_assets.surfaces.crosshair_2x);
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
            void *hit_object = bullet.getHitObject();

            if (hit_object == nullptr)
            {
                continue;
            }

            switch (bullet.getHitObjectType())
            {
            case Bullet::HitObjectType::World:
            {
                World *hit_world = static_cast<World *>(hit_object);

                Vec2<float> bullet_pos = bullet.getPosition();
                hit_world->drawParticles(bullet_pos.x, bullet_pos.y, bullet.getPower(), Particle());
                break;
            }
            default:
                break;
            }
        }

        update_render();
        update_hud();
    }

    return SceneID::Main;
}