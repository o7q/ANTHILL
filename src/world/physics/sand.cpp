#include "../world_physics.hpp"
#include "../../math/random.hpp"

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
        if (Random::genInt(0, 5) == 0)
        {
            p_swap(x, y, _x, _y);
        }
        else
        {
            Particle p_mod = p_orig;

            bool will_collide_with_liquid = false;

            // if the particle is a liquid, darken the sand's color to give the sense of absorbtion
            if (p_get(_x, _y).p_state == Particle::PState::Liquid)
            {
                Color liquid_color = m_particles[_y][_x].liquid_absorption_color;
                p_mod.color = p_mix(p_mod.color, liquid_color, 30.0f, 1.0f, 31.0f * 1.1f, false);
                will_collide_with_liquid = true;
            }

            if (will_collide_with_liquid && Random::genInt(0, 10) != 0)
            {
                return;
            }

            p_set(_x, _y, p_mod);
            p_set(x, y, Particle());
        }

        moved = true;
    };

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