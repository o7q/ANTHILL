#include "p_dynamics_handler.hpp"

#include "math/random.hpp"

void PDynamicsHandler::update_sandstone_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2f start = verlet.getPosition();

    Particle *up    = r_particles.get({po.pos.x, po.pos.y - 1});
    Particle *left  = r_particles.get({po.pos.x - 1, po.pos.y});
    Particle *right = r_particles.get({po.pos.x + 1, po.pos.y});
    Particle *down  = r_particles.get({po.pos.x, po.pos.y + 1});

    bool canDown = true;
    if (can_solid_occupy(down))
    {
        if (!can_solid_occupy(left))
        {
            canDown = Math::Random::unseededRandomInt(0, 10) == 0;
        }

        if (!can_solid_occupy(right))
        {
            canDown = Math::Random::unseededRandomInt(0, 10) == 0;
        }

        if (!can_solid_occupy(up))
        {
            canDown = Math::Random::unseededRandomInt(0, 500) == 0;
        }
    }
    else
    {
        canDown = false;
    }

    if (canDown)
    {
        verlet.addForce({0.0f, m_gravity});
        po.particle->setPhysicsType(Particle::PhysicsType::Sand);
    }

    verlet.integrate(dt);

    Vec2f end = verlet.getPosition();

    handle_particle_trajectory(po, start, end, dt);
    finalize_particle(po);
}
