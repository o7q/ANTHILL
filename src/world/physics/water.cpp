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
            Color mixed_mix_color = p_mix(friend_particle.l_mix_color, p_orig.l_mix_color, 1.0f, 1.0f, 2.0f);

            Particle p_mod = p_orig;

            p_mod.color = mixed_color;
            p_mod.l_mix_color = mixed_mix_color;

            friend_particle.color = mixed_color;
            friend_particle.l_mix_color = mixed_mix_color;

            p_set(x, y, p_mod);
            p_set(_x, _y, friend_particle);
        }
    };

    bool random_mix_up = Random::genInt(0, 40) == 0;
    bool random_mix_down = Random::genInt(0, 20) == 0;
    bool random_mix_side = Random::genInt(0, 30) == 0;

    if (in_bounds(x, y + 1) && random_mix_down)
    {
        mixLiquid(x, y + 1);
    }

    if (in_bounds(x - 1, y) && random_mix_side)
    {
        mixLiquid(x - 1, y);
    }

    if (in_bounds(x + 1, y) && random_mix_side)
    {
        mixLiquid(x + 1, y);
    }

    if (in_bounds(x, y - 1) && random_mix_up)
    {
        mixLiquid(x, y - 1);
    }

    bool randomSandAbsorb = Random::genInt(0, 100) == 0;

    if (in_bounds(x, y + 1) && randomSandAbsorb)
    {
        if (m_particles[y + 1][x].p_mode == Particle::PMode::Sand && m_particles[y + 1][x].s_liquid_saturation < 1.0f)
        {
            p_set(x, y, Particle());

            Particle p_below = m_particles[y + 1][x];

            Color color = p_mix(p_orig.l_mix_color, p_below.color, 5.0f, 1.0f, 6.0f);
            p_below.color = color;
            p_below.s_liquid_saturation = 1.0f;

            p_set(x, y + 1, p_below);

            moved = true;
        }
    }

    bool randomMaterialOutgas = Random::genInt(0, 1000) == 0;

    if (in_bounds(x, y + 1) && randomMaterialOutgas)
    {
        if (m_particles[y + 1][x].p_mode == Particle::PMode::Sand && m_particles[y + 1][x].s_liquid_saturation > 0.9f)
        {
            Particle p_mod = p_orig;
            Particle p_below = m_particles[y + 1][x];

            p_mod.color = p_mix(p_below.color, p_orig.color);

            p_set(x, y, p_mod);
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