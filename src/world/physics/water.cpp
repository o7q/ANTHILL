#include "../world_physics.hpp"

#include "../../math/random.hpp"

#include <cmath>

void WorldPhysics::update_water(Particle particle, int x, int y)
{
    const Particle p_orig = particle;
    bool moved = false;

    auto mixLiquid = [&](int _x, int _y)
    {
        if (m_particles[_y][_x].p_state == Particle::PState::Liquid)
        {
            Particle friend_particle = m_particles[_y][_x];

            Color mixed_color = p_mix(friend_particle.color, p_orig.color, 1.0f, 1.0f, 2.0f);

            Particle p_mod = p_orig;
            p_mod.color = mixed_color;
            friend_particle.color = mixed_color;

            p_set(x, y, p_mod);
            p_set(_x, _y, friend_particle);
        }
    };

    bool randomBleedUp = Random::genInt(0, 40) == 0;
    bool randomBleedDown = Random::genInt(0, 20) == 0;
    bool randomBleedSide = Random::genInt(0, 30) == 0;

    if (in_bounds(x, y + 1) && randomBleedDown)
    {
        mixLiquid(x, y + 1);
    }

    if (in_bounds(x - 1, y) && randomBleedSide)
    {
        mixLiquid(x - 1, y);
    }

    if (in_bounds(x + 1, y) && randomBleedSide)
    {
        mixLiquid(x + 1, y);
    }

    if (in_bounds(x, y - 1) && randomBleedUp)
    {
        mixLiquid(x, y - 1);
    }

    bool randomSandAbsorb = Random::genInt(0, 200) == 0;

    if (in_bounds(x, y + 1) && randomSandAbsorb)
    {
        if (m_particles[y + 1][x].p_mode == Particle::PMode::Sand)
        {
            p_set(x, y, Particle());
            Particle newpart = m_particles[y + 1][x];
            Color t = p_mix(p_orig.liquid_absorption_color, newpart.color, 1.0f, 1.0f, 2.0f);
            newpart.color = t;
            p_set(x, y + 1, newpart);
        }
    }

    if (in_bounds(x, y + 1) && !moved)
    {
        if (m_particles[y + 1][x].isLiquidPassable())
        {
            p_swap(x, y, x, y + 1);
            moved = true;
        }
    }

    if (in_bounds(x - 1, y) && !moved)
    {
        if (m_particles[y][x - 1].isLiquidPassable())
        {
            p_swap(x, y, x - 1, y);
            moved = true;
        }
    }

    if (in_bounds(x + 1, y) && !moved)
    {
        if (m_particles[y][x + 1].isLiquidPassable())
        {
            p_swap(x, y, x + 1, y);
            moved = true;
        }
    }
}