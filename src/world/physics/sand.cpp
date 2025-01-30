#include "../world_physics.hpp"
#include "../../math/random.hpp"

void WorldPhysics::update_sand(Particle particle, int x, int y)
{
    // const Particle p_orig = particle;
    Particle p_mod = particle;
    bool moved = false;

    auto move = [&](int _x, int _y)
    {
        // random chance to make solid passable float above (1 in 4 chance)
        if (Random::genInt(0, 5) == 0)
        {
            p_swap(x, y, _x, _y);
        }
        else
        {
            bool will_collide_with_liquid = false;

            // if the particle is a liquid, darken the sand's color to give the sense of absorbtion
            if (p_get(_x, _y).p_state == Particle::PState::Liquid)
            {
                p_mod.color = Color(p_mod.color.r / 1.1f, p_mod.color.g / 1.1f, p_mod.color.b / 1.1f);
                will_collide_with_liquid = true;
            }

            if (will_collide_with_liquid && Random::genInt(0, 10) != 0)
            {
                return;
            }

            p_set(_x, _y, p_mod);
            p_set(x, y, Particle());
        }
    };

    if (in_bounds(x, y + 1) && !moved)
    {
        if (m_particles[y + 1][x].isSolidPassable())
        {
            move(x, y + 1);
            moved = true;
        }
    }

    if (in_bounds(x - 1, y + 1) && !moved)
    {
        if (m_particles[y + 1][x - 1].isSolidPassable())
        {
            move(x - 1, y + 1);
            moved = true;
        }
    }

    if (in_bounds(x + 1, y + 1) && !moved)
    {
        if (m_particles[y + 1][x + 1].isSolidPassable())
        {
            move(x + 1, y + 1);
            moved = true;
        }
    }
}