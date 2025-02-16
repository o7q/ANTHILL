#include "world.hpp"

#include <algorithm>

#include "../engine/math/vector.hpp"
#include "../engine/math/segment.hpp"

void World::generate_world_hitbox(BoundingBox *box)
{
    int y_start = 0;
    int y_end   = 0;

    int x_start = 0;
    int x_end   = 0;

    if (box != nullptr)
    {
        y_start = std::clamp(box->getP1().toInt().y, 0, m_size.y - 1);
        y_end   = std::clamp(box->getP4().toInt().y, 0, m_size.y - 1) - 1;

        x_start = std::clamp(box->getP1().toInt().x, 0, m_size.x - 1);
        x_end   = std::clamp(box->getP2().toInt().x, 0, m_size.x - 1) - 1;
    }
    else
    {
        y_start = 0;
        y_end   = m_size.y - 1;

        x_start = 0;
        x_end   = m_size.x - 1;
    }

    m_world_hitbox.clear();

    for (int y = y_start; y < y_end; ++y)
    {
        for (int x = x_start; x < x_end; ++x)
        {
            // [d][c]
            // [a][b]

            Particle p_a = m_particles[y + 1][x    ];
            Particle p_b = m_particles[y + 1][x + 1];
            Particle p_c = m_particles[y    ][x + 1];
            Particle p_d = m_particles[y    ][x    ];
            int a = p_a.p_collision_type == Particle::PCollisionType::Solid && p_a.solid_enable_collision ? 1 : 0;
            int b = p_b.p_collision_type == Particle::PCollisionType::Solid && p_b.solid_enable_collision ? 1 : 0;
            int c = p_c.p_collision_type == Particle::PCollisionType::Solid && p_c.solid_enable_collision ? 1 : 0;
            int d = p_d.p_collision_type == Particle::PCollisionType::Solid && p_d.solid_enable_collision ? 1 : 0;
            
            int index = a * 1 + b * 2 + c * 4 + d * 8;

            Vec2<float> left   = Vec2<float>(x       , y + 0.5f) + m_position.toFloat();
            Vec2<float> right  = Vec2<float>(x + 1.0f, y + 0.5f) + m_position.toFloat();
            Vec2<float> top    = Vec2<float>(x + 0.5f, y       ) + m_position.toFloat();
            Vec2<float> bottom = Vec2<float>(x + 0.5f, y + 1.0f) + m_position.toFloat();

            switch (index)
            {
            case 0:
                break;
            case 1:
                m_world_hitbox.push_back(Segment(left  , bottom));
                break;
            case 2:
                m_world_hitbox.push_back(Segment(bottom, right));
                break;
            case 3:
                m_world_hitbox.push_back(Segment(left  , right));
                break;
            case 4:
                m_world_hitbox.push_back(Segment(top   , right));
                break;
            case 5:
                m_world_hitbox.push_back(Segment(left  , top));
                m_world_hitbox.push_back(Segment(bottom, right));
                break;
            case 6:
                m_world_hitbox.push_back(Segment(top   , bottom));
                break;
            case 7:
                m_world_hitbox.push_back(Segment(left  , top));
                break;
            case 8:
                m_world_hitbox.push_back(Segment(left  , top));
                break;
            case 9:
                m_world_hitbox.push_back(Segment(top   , bottom));
                break;
            case 10:
                m_world_hitbox.push_back(Segment(left  , bottom));
                m_world_hitbox.push_back(Segment(top   , right));
                break;
            case 11:
                m_world_hitbox.push_back(Segment(top   , right));
                break;
            case 12:
                m_world_hitbox.push_back(Segment(left  , right));
                break;
            case 13:
                m_world_hitbox.push_back(Segment(bottom, right));
                break;
            case 14:
                m_world_hitbox.push_back(Segment(left  , bottom));
                break;
            case 15:
                break;
            }
        }
    }
}