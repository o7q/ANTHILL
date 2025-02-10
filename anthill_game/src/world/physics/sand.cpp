#include "world_physics.hpp"
#include "../../math/random.hpp"

#include <cmath>

// f_value1 = dampness controller

void WorldPhysics::update_sand(Particle particle, int x, int y)
{
    const Particle p_orig = particle;
    bool moved = false;

    auto move = [&](int _x, int _y)
    {
        if (!m_particles[_y][_x].isSolidPassable())
        {
            return;
        }

        // random chance to make particle below float above (1 oh in 4 chance)
        Particle p_mod = p_orig;

        bool will_collide_with_liquid = false;

        // decide if the sand will collide with liquid
        if (p_get(_x, _y).p_state == Particle::PState::Liquid)
        {
            will_collide_with_liquid = true;
        }

        bool float_on_water = Random::genInt(0, 10) != 0;
        if (will_collide_with_liquid && float_on_water)
        {
            return;
        }

        bool liquid_floats_above = Random::genInt(0, 5) == 0;
        if ((will_collide_with_liquid && liquid_floats_above) || p_orig.f_value1 > 0.9f)
        {
            p_swap(x, y, _x, _y);
            moved = true;
            return;
        }

        if (will_collide_with_liquid)
        {
            Color liquid_mix_color = m_particles[_y][_x].mix_color;
            p_mod.color = p_mix(p_mod.color, liquid_mix_color, 1.0f, 3.0f, 4.0f, false);
            p_mod.f_value1 = 1.0f;
        }

        p_set(_x, _y, p_mod);
        p_set(x, y, Particle());

        moved = true;
    };

    // i don't fully know how this works, but it does >:3
    auto transferMoisture = [&](int _x, int _y)
    {
        if (p_orig.f_value1 > 0.0f && m_particles[_y][_x].p_mode == Particle::PMode::Sand)
        {
            Particle p_mod = m_particles[_y][_x];
            p_mod.f_value1 = std::fabs((p_orig.f_value1 - p_mod.f_value1)) / 2.0f;
            p_mod.color = p_mix(p_orig.color, p_mod.color, 1.0f, 1.0f, 2.0f, false);
            p_set(_x, _y, p_mod);
        }
    };

    // allow for a damp sand particle to outgas its substance into the water
    bool should_damp_particle_outgas = Random::genInt(0, 250) == 0;
    if (in_bounds(x, y - 1) && should_damp_particle_outgas)
    {
        if (m_particles[y - 1][x].p_mode == Particle::PMode::Water && m_particles[y][x].f_value1 > 0.9f)
        {
            Particle p_mod = m_particles[y - 1][x];

            p_mod.color = p_mix(p_orig.color, p_mod.color);

            p_set(x, y - 1, p_mod);
        }
    }

    bool bleed_down = Random::genInt(0, 500) == 0;
    bool bleed_side = Random::genInt(0, 1000) == 0;
    bool bleed_up = Random::genInt(0, 1500) == 0;

    if (in_bounds(x, y + 1) && bleed_down)
    {
        transferMoisture(x, y + 1);
    }

    if (in_bounds(x - 1, y) && bleed_side)
    {
        transferMoisture(x - 1, y);
    }

    if (in_bounds(x + 1, y) && bleed_side)
    {
        transferMoisture(x + 1, y);
    }

    if (in_bounds(x, y - 1) && bleed_up)
    {
        transferMoisture(x, y - 1);
    }

    if (in_bounds(x, y + 1) && !moved)
    {
        move(x, y + 1);
    }

    if (in_bounds(x - 1, y + 1) && !moved)
    {
        move(x - 1, y + 1);
    }

    if (in_bounds(x + 1, y + 1) && !moved)
    {
        move(x + 1, y + 1);
    }
}