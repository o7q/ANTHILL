#include "p_dynamics_handler.hpp"

#include "utils/math/random.hpp"
#include "utils/physics/verlet.hpp"

void PDynamicsHandler::update_water_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2<float> start = verlet.getPosition();

    Particle *left = r_particles.get(po.x - 1, po.y);
    Particle *right = r_particles.get(po.x + 1, po.y);
    Particle *down = r_particles.get(po.x, po.y + 1);

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
        verlet.addVelocity(0.0f, m_gravity, dt);
    }

    if (canLeft && canRight)
    {
        switch (Utils::Math::Random::weakRandInt(0, 2))
        {
        case 0:
            verlet.addVelocity(-0.3f, 0, dt);
            break;
        case 1:
            verlet.addVelocity(0.3f, 0, dt);
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        verlet.addVelocity(-0.3f, 0, dt);
    }
    else if (canRight)
    {
        verlet.addVelocity(0.3f, 0, dt);
    }

    verlet.integrate(dt);

    Vec2<float> end = verlet.getPosition();

    resolve_particle_collision(po, start, end, dt);
    finalize_particle(po);
}
