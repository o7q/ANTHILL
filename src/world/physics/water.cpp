#include "world_physics.hpp"

#include "../../math/random.hpp"

#include <cmath>

void WorldPhysics::update_water(Particle particle, int x, int y)
{
    const Particle p_orig = particle;
    bool moved = false;

    // function to mix liquids together
    auto mixLiquid = [&](int _x, int _y)
    {
        if (m_particles[_y][_x].p_state == Particle::PState::Liquid)
        {
            Particle p_to_mix = m_particles[_y][_x];

            Color mixed_color = p_mix(p_orig.color, p_to_mix.color, 1.0f, 1.0f, 2.0f, true);
            Color mixed_mix_color = p_mix(p_orig.mix_color, p_to_mix.mix_color, 1.0f, 1.0f, 2.0f, true);

            Particle p_mod = p_orig;

            p_mod.color = mixed_color;
            p_mod.mix_color = mixed_mix_color;

            p_to_mix.color = mixed_color;
            p_to_mix.mix_color = mixed_mix_color;

            p_set(x, y, p_mod);
            p_set(_x, _y, p_to_mix);
        }
    };

    bool mix_down = Random::genInt(0, 20) == 0;
    bool mix_side = Random::genInt(0, 30) == 0;
    bool mix_up = Random::genInt(0, 40) == 0;

    if (in_bounds(x, y + 1) && mix_down)
    {
        mixLiquid(x, y + 1);
    }

    if (in_bounds(x - 1, y) && mix_side)
    {
        mixLiquid(x - 1, y);
    }

    if (in_bounds(x + 1, y) && mix_side)
    {
        mixLiquid(x + 1, y);
    }

    if (in_bounds(x, y - 1) && mix_up)
    {
        mixLiquid(x, y - 1);
    }

    bool should_be_absorbed = Random::genInt(0, 100) == 0;
    if (in_bounds(x, y + 1) && should_be_absorbed)
    {
        // should the liquid be absorbed by a sand particle?
        if (m_particles[y + 1][x].p_mode == Particle::PMode::Sand && m_particles[y + 1][x].f_value1 < 1.0f)
        {
            p_set(x, y, Particle());

            Particle p_below = m_particles[y + 1][x];

            Color color = p_mix(p_orig.mix_color, p_below.color, 5.0f, 1.0f, 6.0f);
            p_below.color = color;
            p_below.f_value1 = 1.0f;

            p_set(x, y + 1, p_below);

            moved = true;
        }
    }

    if (in_bounds(x, y + 1) && !moved)
    {
        if (m_particles[y + 1][x].isLiquidPassable())
        {
            p_move(x, y, x, y + 1);
            moved = true;
        }
    }

    if (in_bounds(x - 1, y) && !moved)
    {
        if (m_particles[y][x - 1].isLiquidPassable())
        {
            p_move(x, y, x - 1, y);
            moved = true;
        }
    }

    if (in_bounds(x + 1, y) && !moved)
    {
        if (m_particles[y][x + 1].isLiquidPassable())
        {
            p_move(x, y, x + 1, y);
            moved = true;
        }
    }
}