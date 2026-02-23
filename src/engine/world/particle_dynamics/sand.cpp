#include "p_dynamics_handler.hpp"

#include "engine/math/random.hpp"
#include "engine/math/verlet.hpp"

void PDynamicsHandler::update_sand_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2<float> start = verlet.getPosition();

    if (Particle *below = r_particles.get(po.x, po.y + 1))
    {
        if (below->isGas())
        {
            verlet.addForce(0.0f, m_gravity);
        }
    }

    Particle *leftDown = r_particles.get(po.x - 1, po.y + 1);
    Particle *rightDown = r_particles.get(po.x + 1, po.y + 1);
    Particle *down = r_particles.get(po.x, po.y + 1);

    bool canLeft = false, canRight = false;

    if (leftDown && down)
    {
        if (leftDown->isGas() && !down->isGas())
        {
            canLeft = true;
        }
    }
    if (rightDown && down)
    {
        if (rightDown->isGas() && !down->isGas())
        {
            canRight = true;
        }
    }

    if (canLeft && canRight)
    {
        switch (Math::weakRandInt(0, 2))
        {
        case 0:
            verlet.addForce(-0.1, 0);
            break;
        case 1:
            verlet.addForce(0.1, 0);
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
