#include "bullet.hpp"

#include "../engine/math/segment.hpp"

void Bullet::checkWorld(World *world, float dt)
{
    // if (hit())
    // {
    //     return;
    // }

    // Vec2<float> future_position = m_position + Vec2<float>(m_dx, m_dy) * m_speed * dt;
    // Segment bullet_trajectory(m_position, future_position);

    // for (const Segment &segment : world->getWorldHitbox())
    // {
    //     Segment::IData i_data = bullet_trajectory.checkSegmentIntersection(segment);
    //     if (i_data.intersecting)
    //     {
    //         m_position = i_data.position;

    //         m_hit_object = world;
    //         m_hit_object_type = HitObjectType::World;
            
    //         return;
    //     }
    // }

    // Particle p = world->getParticle(m_position.x, m_position.y);
    // if (p.p_collision_type == Particle::PCollisionType::Solid && p.solid_enable_collision)
    // {
    //     m_hit_object = world;
    //     m_hit_object_type = HitObjectType::World;
    // }
}