#include "engine/utils/math.hpp"
#include "engine/verlet.hpp"
#include "p_dynamics_handler.hpp"

void PDynamicsHandler::update_water_particle(ParticleSubject ps, float dt)
{
    VerletBody &verlet = ps.particle->getVerlet();

    Vec2<float> start = verlet.getPosition();

    if (Particle *below = r_particles.get(ps.x, ps.y + 1))
    {
        if (below->isAir())
        {
            ps.particle->getVerlet().addForce(0, 0.1);
        }
    }

    Particle *left = r_particles.get(ps.x - 1, ps.y);
    Particle *right = r_particles.get(ps.x - 1, ps.y);
    Particle *down = r_particles.get(ps.x, ps.y + 1);

    bool canLeft = false, canRight = false;

    if (left && down)
    {
        if (left->isAir() && !down->isAir())
        {
            canLeft = true;
        }
    }
    if (right && down)
    {
        if (right->isAir() && !down->isAir())
        {
            canRight = true;
        }
    }

    if (canLeft && canRight)
    {
        switch (MathUtils::weakRandInt(0, 2))
        {
        case 0:
            ps.particle->getVerlet().addForce(-0.3, 0);
            break;
        case 1:
            ps.particle->getVerlet().addForce(0.3, 0);
            break;
        default:
            break;
        }
    }
    else if (canLeft)
    {
        ps.particle->getVerlet().addForce(-0.3, 0);
    }
    else if (canRight)
    {
        ps.particle->getVerlet().addForce(0.3, 0);
    }

    ps.particle->getVerlet().update(dt);

    Vec2<float> end = verlet.getPosition();

    resolve_particle_collision(ps, start, end, dt);
    move_particle(ps);
}
