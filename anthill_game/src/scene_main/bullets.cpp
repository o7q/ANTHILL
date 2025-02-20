#include "scene_main.hpp"

void MainScene::update_bullets()
{
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
            hit_world->drawParticles(bullet_pos.x, bullet_pos.y, bullet.getPower(), Particle(), World::DrawShape::Circle, true);
            break;
        }
        default:
            break;
        }
    }
}