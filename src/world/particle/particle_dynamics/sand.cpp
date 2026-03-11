#include "p_dynamics_handler.hpp"

#include "utils/math/random.hpp"
#include "utils/physics/verlet.hpp"

void PDynamicsHandler::update_sand_particle(ParticleObject po, float dt)
{
    VerletBody &verlet = po.particle->getVerlet();

    Vec2<float> start = verlet.getPosition();

    Particle *leftDown = r_particles.get(po.x - 1, po.y + 1);
    Particle *rightDown = r_particles.get(po.x + 1, po.y + 1);
    Particle *down = r_particles.get(po.x, po.y + 1);

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
        verlet.addForce(0.0f, m_gravity);
    }

    if (canLeft && canRight)
    {
        switch (Utils::Math::Random::weakRandInt(0, 2))
        {
        case 0:
            verlet.addForce(-0.1f, 0);
            break;
        case 1:
            verlet.addForce(0.1f, 0);
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        verlet.addForce(-0.3f, 0);
    }
    else if (canRight)
    {
        verlet.addForce(0.3f, 0);
    }

    verlet.integrate(dt);

    Vec2<float> end = verlet.getPosition();

    resolve_particle_collision(po, start, end, dt);
    finalize_particle(po);
}
