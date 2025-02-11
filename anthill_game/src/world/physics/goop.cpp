#include "world_physics.hpp"

#include "../../math/random.hpp"

void WorldPhysics::update_goop(Particle particle, int x, int y)
{
    // const Particle p_orig = particle;
    bool moved = false;

    bool goop_side = Random::genInt(0, 3) == 0;

    if (in_bounds(x, y + 1))
    {
        if (p_get(x, y + 1).isLiquidPassable())
        {
            p_move(x, y, x, y + 1);
            moved = true;
        }
    }

    if (in_bounds(x - 1, y) && !moved && goop_side)
    {
        if (p_get(x - 1, y).isLiquidPassable())
        {
            p_move(x, y, x - 1, y);
            moved = true;
        }
    }

    if (in_bounds(x + 1, y) && !moved && goop_side)
    {
        if (p_get(x + 1, y).isLiquidPassable())
        {
            p_move(x, y, x + 1, y);
            moved = true;
        }
    }
}