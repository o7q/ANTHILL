#include "engine/utils/math.hpp"
#include "engine/verlet.hpp"
#include "p_dynamics_handler.hpp"

void PDynamicsHandler::update_smoke_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2<float> start = verlet.getPosition();

    if (Particle *above = r_particles.get(po.x, po.y - 1))
    {
        if (above->isAir())
        {
            verlet.addForce(0, -0.03);
        }
    }

    Particle *left = r_particles.get(po.x - 1, po.y);
    Particle *right = r_particles.get(po.x + 1, po.y);
    Particle *up = r_particles.get(po.x, po.y - 1);

    bool canLeft = false, canRight = false;

    if (left && up)
    {
        if (left->isAir() && !up->isAir())
        {
            canLeft = true;
        }
    }
    if (right && up)
    {
        if (right->isAir() && !up->isAir())
        {
            canRight = true;
        }
    }

    if (canLeft && canRight)
    {
        switch (MathUtils::weakRandInt(0, 2))
        {
        case 0:
            verlet.addForce(-0.07, 0);
            break;
        case 1:
            verlet.addForce(0.07, 0);
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        verlet.addForce(-0.07, 0);
    }
    else if (canRight)
    {
        verlet.addForce(0.07, 0);
    }

    verlet.update(dt);

    Vec2<float> end = verlet.getPosition();

    resolve_particle_collision(po, start, end, dt);
    finalize_particle(po);
}
