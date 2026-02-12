#include "world_physics.hpp"

#include <algorithm>

#include "../engine/math/random.hpp"
#include "../engine/math/bounding_box.hpp"

void WorldPhysics::updateParticles(BoundingBox *box)
{
    int y_start = 0;
    int y_end = 0;

    int x1_start = 0;
    int x1_end = 0;

    int x2_start = 0;
    int x2_end = 0;

    if (box != nullptr)
    {
        y_start  = std::clamp(box->getP4().toInt().y, 0, m_size.y - 1);
        y_end    = std::clamp(box->getP1().toInt().y, 0, m_size.y - 1);

        x1_start = std::clamp(box->getP1().toInt().x, 0, m_size.x - 1);
        x1_end   = std::clamp(box->getP2().toInt().x, 0, m_size.x - 1);

        x2_start = x1_end;
        x2_end   = x1_start;
    }
    else
    {
        y_start  = m_size.y - 1;
        y_end    = 0;

        x1_start = 0;
        x1_end   = m_size.x;

        x2_start = m_size.x - 1;
        x2_end   = 0;
    }

    for (int y = y_start; y >= y_end; --y)
    {
        if (Random::genInt(0, 2) == 0)
        {
            for (int x = x1_start; x < x1_end; ++x)
            {
                update_particle(x, y);
            }
        }
        else
        {
            for (int x = x2_start; x >= x2_end; --x)
            {
                update_particle(x, y);
            }
        }
    }
}

void WorldPhysics::update_particle(int x, int y)
{
    Particle particle = m_particles[y][x];

    switch (m_particles[y][x].p_mode)
    {
    case Particle::PMode::None:
        break;
    case Particle::PMode::Sand:
        update_sand(particle, x, y);
        break;
    case Particle::PMode::Water:
        update_water(particle, x, y);
        break;
    case Particle::PMode::Smoke:
        update_smoke(particle, x, y);
        break;
    case Particle::PMode::Goop:
        update_goop(particle, x, y);
        break;
    }
}