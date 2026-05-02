#include "p_dynamics_handler.hpp"

#include "math/random.hpp"

void PDynamicsHandler::update_smoke_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2f start = verlet.getPosition();

    Particle *left  = r_particles.get({po.pos.x - 1, po.pos.y});
    Particle *right = r_particles.get({po.pos.x + 1, po.pos.y});
    Particle *up    = r_particles.get({po.pos.x, po.pos.y - 1});

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
        verlet.addVelocity({0.0f, m_gravity - 0.11f}, dt);
    }

    if (canLeft && canRight)
    {
        switch (Math::Random::unseededRandomInt(0, 2))
        {
        case 0:
            verlet.addForce({-0.03f, 0.0f});
            break;
        case 1:
            verlet.addForce({0.03f, 0.0f});
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        verlet.addForce({-0.03f, 0.0f});
    }
    else if (canRight)
    {
        verlet.addForce({0.03f, 0.0f});
    }

    verlet.integrate(dt);

    Vec2f end = verlet.getPosition();

    handle_particle_trajectory(po, start, end, dt);
    finalize_particle(po);
}
