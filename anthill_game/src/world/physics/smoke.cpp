#include "world_physics.hpp"
#include "../../math/random.hpp"

#include <cmath>

void WorldPhysics::update_smoke(Particle particle, int x, int y)
{
    // const Particle p_orig = particle;
    bool moved = false;

    auto move = [&](int _x, int _y)
    {
        if (p_get(_x, _y).isAir())
        {
            p_swap(x, y, _x, _y);
            moved = true;
        }
    };

    bool move_up = Random::genInt(0, 4) == 0;
    bool move_side = Random::genInt(0, 3) == 0;

    if (in_bounds(x, y - 1) && !moved && move_up)
    {
        move(x, y - 1);
    }

    if (move_side)
    {
        bool left_right = Random::genInt(0, 2) == 0;

        if (left_right == 0)
        {
            if (in_bounds(x - 1, y) && !moved && move_side)
            {
                move(x - 1, y);
            }
        }
        else
        {
            if (in_bounds(x + 1, y) && !moved && move_side)
            {
                move(x + 1, y);
            }
        }
    }
}