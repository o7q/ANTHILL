#include "../world_physics.hpp"
#include "../../math/random.hpp"

#include <cmath>

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

        // random chance to make particle below float above (1 in 4 chance)
        Particle p_mod = p_orig;

        bool will_collide_with_liquid = false;

        // if the particle is a liquid, darken the sand's color to give the sense of absorbtion
        if (p_get(_x, _y).p_state == Particle::PState::Liquid)
        {
            will_collide_with_liquid = true;
        }

        if (will_collide_with_liquid && Random::genInt(0, 10) != 0)
        {
            return;
        }

        if (will_collide_with_liquid && Random::genInt(0, 5) == 0)
        {
            p_swap(x, y, _x, _y);
            moved = true;
            return;
        }

        if (will_collide_with_liquid)
        {
            Color liquid_mix_color = m_particles[_y][_x].l_mix_color;
            p_mod.color = p_mix(p_mod.color, liquid_mix_color, 10.0f, 1.0f, 11.0f * 1.1f, false);
            p_mod.s_liquid_saturation = 1.0f;
        }

        p_set(_x, _y, p_mod);
        p_set(x, y, Particle());

        moved = true;
    };

    auto transferMoisture = [&](int _x, int _y)
    {
        if (p_orig.s_liquid_saturation > 0.0f && m_particles[_y][_x].p_mode == Particle::PMode::Sand)
        {
            Particle p_mod = m_particles[_y][_x];
            p_mod.s_liquid_saturation = std::fabs((p_orig.s_liquid_saturation - p_mod.s_liquid_saturation)) / 2.0f;
            p_mod.color = p_mix(p_orig.color, p_mod.color, 1.0f, 1.0f, 2.0f, false);
            p_set(_x, _y, p_mod);
        }
    };

    bool randomBleedDown = Random::genInt(0, 100) == 0;
    bool randomBleedSide = Random::genInt(0, 200) == 0;
    bool randomBleedUp = Random::genInt(0, 300) == 0;

    if (in_bounds(x, y - 1) && randomBleedUp)
    {
        transferMoisture(x, y - 1);
    }

    if (in_bounds(x, y + 1) && randomBleedDown)
    {
        transferMoisture(x, y + 1);
    }

    if (in_bounds(x - 1, y) && randomBleedSide)
    {
        transferMoisture(x - 1, y);
    }

    if (in_bounds(x + 1, y) && randomBleedSide)
    {
        transferMoisture(x + 1, y);
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