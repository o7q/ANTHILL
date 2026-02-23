#include "engine/utils/math.hpp"
#include "engine/verlet.hpp"
#include "p_dynamics_handler.hpp"

void PDynamicsHandler::update_water_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2<float> start = verlet.getPosition();

    if (Particle *below = r_particles.get(po.x, po.y + 1))
    {
        if (below->isGas())
        {
            verlet.addForce(0, 0.1);
        }
    }

    Particle *left = r_particles.get(po.x - 1, po.y);
    Particle *right = r_particles.get(po.x + 1, po.y);
    Particle *down = r_particles.get(po.x, po.y + 1);

    bool canLeft = false, canRight = false;

    if (left && down)
    {
        if (left->isGas() && !down->isGas())
        {
            canLeft = true;
        }
    }
    if (right && down)
    {
        if (right->isGas() && !down->isGas())
        {
            canRight = true;
        }
    }

    if (canLeft && canRight)
    {
        switch (MathUtils::weakRandInt(0, 2))
        {
        case 0:
            verlet.addForce(-0.3, 0);
            break;
        case 1:
            verlet.addForce(0.3, 0);
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        verlet.addForce(-0.3, 0);
    }
    else if (canRight)
    {
        verlet.addForce(0.3, 0);
    }

    verlet.update(dt);

    Vec2<float> end = verlet.getPosition();

    resolve_particle_collision(po, start, end, dt);
    finalize_particle(po);
}
