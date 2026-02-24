#include "p_dynamics_handler.hpp"

#include "engine/math/random.hpp"
#include "engine/math/verlet.hpp"

void PDynamicsHandler::update_smoke_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2<float> start = verlet.getPosition();

    Particle *left = r_particles.get(po.x - 1, po.y);
    Particle *right = r_particles.get(po.x + 1, po.y);
    Particle *up = r_particles.get(po.x, po.y - 1);

    bool canUp = false, canLeft = false, canRight = false;

    if (can_gas_occupy(up))
    {
        canUp = true;
    }

    if (can_gas_occupy(left) && !can_gas_occupy(up))
    {
        canLeft = true;
    }

    if (can_gas_occupy(right) && !can_gas_occupy(up))
    {
        canRight = true;
    }

    if (canUp)
    {
        verlet.addVelocity(0.0f, m_gravity - 0.11f, dt);
    }

    if (canLeft && canRight)
    {
        switch (Math::weakRandInt(0, 2))
        {
        case 0:
            verlet.addForce(-0.03, 0);
            break;
        case 1:
            verlet.addForce(0.03, 0);
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        verlet.addForce(-0.03, 0);
    }
    else if (canRight)
    {
        verlet.addForce(0.03, 0);
    }

    verlet.update(dt);

    Vec2<float> end = verlet.getPosition();

    resolve_particle_collision(po, start, end, dt);
    finalize_particle(po);
}
