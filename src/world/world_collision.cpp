#include "world.hpp"

#include "../math/vector.hpp"
#include "../math/segment.hpp"

void World::generate_world_collision()
{
    m_world_collision.clear();

    for (int y = 0; y < m_size.y - 1; ++y)
    {
        for (int x = 0; x < m_size.x - 1; ++x)
        {
            // [d][c]
            // [a][b]

            int a = m_particles[y + 1][x    ].p_collision_type == Particle::PCollisionType::Solid ? 1 : 0;
            int b = m_particles[y + 1][x + 1].p_collision_type == Particle::PCollisionType::Solid ? 1 : 0;
            int c = m_particles[y    ][x + 1].p_collision_type == Particle::PCollisionType::Solid ? 1 : 0;
            int d = m_particles[y    ][x    ].p_collision_type == Particle::PCollisionType::Solid ? 1 : 0;
            int index = a * 1 + b * 2 + c * 4 + d * 8;

            Vec2<float> half_size = Vec2<float>(m_size.x / 2.0f, m_size.y / 2.0f);
            Vec2<float> left      = Vec2<float>(x              , y + 0.5f) - half_size;
            Vec2<float> right     = Vec2<float>(x + 1.0f       , y + 0.5f) - half_size;
            Vec2<float> top       = Vec2<float>(x + 0.5f       , y)        - half_size;
            Vec2<float> bottom    = Vec2<float>(x + 0.5f       , y + 1.0f) - half_size;

            switch (index)
            {
            case 0:
                break;
            case 1:
                m_world_collision.push_back(Segment(left, bottom));
                break;
            case 2:
                m_world_collision.push_back(Segment(bottom, right));
                break;
            case 3:
                m_world_collision.push_back(Segment(left, right));
                break;
            case 4:
                m_world_collision.push_back(Segment(top, right));
                break;
            case 5:
                m_world_collision.push_back(Segment(left, top));
                m_world_collision.push_back(Segment(bottom, right));
                break;
            case 6:
                m_world_collision.push_back(Segment(top, bottom));
                break;
            case 7:
                m_world_collision.push_back(Segment(left, top));
                break;
            case 8:
                m_world_collision.push_back(Segment(left, top));
                break;
            case 9:
                m_world_collision.push_back(Segment(top, bottom));
                break;
            case 10:
                m_world_collision.push_back(Segment(left, bottom));
                m_world_collision.push_back(Segment(top, right));
                break;
            case 11:
                m_world_collision.push_back(Segment(top, right));
                break;
            case 12:
                m_world_collision.push_back(Segment(left, right));
                break;
            case 13:
                m_world_collision.push_back(Segment(bottom, right));
                break;
            case 14:
                m_world_collision.push_back(Segment(left, bottom));
                break;
            case 15:
                break;
            }
        }
    }
}