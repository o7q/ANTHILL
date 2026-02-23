#include "engine/utils/math.hpp"
#include "engine/verlet.hpp"
#include "p_dynamics_handler.hpp"

void PDynamicsHandler::update_sand_particle(ParticleSubject ps, float dt)
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

    Particle *leftDown = r_particles.get(ps.x - 1, ps.y + 1);
    Particle *rightDown = r_particles.get(ps.x - 1, ps.y + 1);
    Particle *down = r_particles.get(ps.x, ps.y + 1);
    switch (MathUtils::weakRandInt(0, 4))
    {
    case 0:
        if (leftDown && down)
        {
            if (leftDown->isAir() && !down->isAir())
            {
                ps.particle->getVerlet().addForce(-0.1, 0);
            }
        }
        break;
    case 1:
        if (rightDown && down)
        {
            if (rightDown->isAir() && !down->isAir())
            {
                ps.particle->getVerlet().addForce(0.1, 0);
            }
        }
    default:
        break;
    }

    ps.particle->getVerlet().update(dt);

    Vec2<float> end = verlet.getPosition();

    resolve_particle_collision(ps, start, end, dt);
    move_particle(ps);
}
