#include "p_dynamics_handler.hpp"

#include "math/physics/verlet.hpp"
#include "math/random.hpp"

void PDynamicsHandler::update_sand_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2f start = verlet.getPosition();

    Particle *leftDown  = r_particles.get({po.pos.x - 1, po.pos.y + 1});
    Particle *rightDown = r_particles.get({po.pos.x + 1, po.pos.y + 1});
    Particle *down      = r_particles.get({po.pos.x, po.pos.y + 1});

    bool canDown = false, canLeft = false, canRight = false;

    if (can_solid_occupy(down))
    {
        canDown = true;
    }

    if (can_solid_occupy(leftDown) && !can_solid_occupy(down))
    {
        canLeft = true;
    }

    if (can_solid_occupy(rightDown) && !can_solid_occupy(down))
    {
        canRight = true;
    }

    if (canDown)
    {
        verlet.addForce({0.0f, m_gravity});
    }

    if (canLeft && canRight)
    {
        switch (Math::Random::unseededRandomInt(0, 2))
        {
        case 0:
            verlet.addForce({-0.1f, 0.0f});
            break;
        case 1:
            verlet.addForce({0.1f, 0.0f});
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        verlet.addForce({-0.3f, 0.0f});
    }
    else if (canRight)
    {
        verlet.addForce({0.3f, 0.0f});
    }

    verlet.integrate(dt);

    Vec2f end = verlet.getPosition();

    handle_particle_trajectory(po, start, end, dt);
    finalize_particle(po);
}
