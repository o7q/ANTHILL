#include "p_dynamics_handler.hpp"

#include "px/math/random.hpp"

void PDynamicsHandler::update_water_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2f start = verlet.getPosition();

    Particle *left  = r_particles.get({po.pos.x - 1, po.pos.y});
    Particle *right = r_particles.get({po.pos.x + 1, po.pos.y});
    Particle *down  = r_particles.get({po.pos.x, po.pos.y + 1});

    bool canDown = false, canLeft = false, canRight = false;

    if (can_liquid_occupy(down))
    {
        canDown = true;
    }

    if (can_liquid_occupy(left) && !can_liquid_occupy(down))
    {
        canLeft = true;
    }

    if (can_liquid_occupy(right) && !can_liquid_occupy(down))
    {
        canRight = true;
    }

    if (canDown)
    {
        verlet.addVelocity({0.0f, m_gravity}, dt);
    }

    if (canLeft && canRight)
    {
        switch (Math::Random::unseededRandomInt(0, 2))
        {
        case 0:
            verlet.addVelocity({-0.3f, 0.0f}, dt);
            break;
        case 1:
            verlet.addVelocity({0.3f, 0.0f}, dt);
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        verlet.addVelocity({-0.3f, 0.0f}, dt);
    }
    else if (canRight)
    {
        verlet.addVelocity({0.3f, 0.0f}, dt);
    }

    verlet.integrate(dt);

    Vec2f end = verlet.getPosition();

    handle_particle_trajectory(po, start, end, dt);
    finalize_particle(po);
}
