#include "p_dynamics_handler.hpp"

#include "px/utils/line.hpp"
#include "px/utils/physics.hpp"

void PDynamicsHandler::handle_particle_trajectory(ParticleObject po, px::Vec2f start, px::Vec2f end, float dt)
{
    px::Vec2i currentCheck  = start.toGrid();
    px::Vec2i previousCheck = start.toGrid();
    Particle *hitParticle   = nullptr;
    bool hit                = false;

    auto function = [&](px::Vec2i pos)
    {
        currentCheck = pos;

        Particle *next = r_particles.get(pos);

        if (next == po.particle)
        {
            return false;
        }

        if (!next)
        {
            hit = true;
            return true;
        }

        bool canPass = false;

        if (po.particle->isSolid() && can_solid_occupy(next))
        {
            canPass = true;
        }
        else if (po.particle->isLiquid() && can_liquid_occupy(next))
        {
            canPass = true;
        }
        else if (po.particle->isGas() && can_gas_occupy(next))
        {
            canPass = true;
        }

        if (!canPass)
        {
            hit         = true;
            hitParticle = next;
            return true;
        }

        previousCheck = pos;
        return false;
    };

    px::Lines::bresenhamLine({start.toGrid(), end.toGrid()}, function);

    if (!hit)
    {
        return;
    }

    if (hitParticle)
    {
        resolve_particle_collision_against_other(po, hitParticle, currentCheck, previousCheck, dt);
    }
    else
    {
        resolve_particle_collision_against_null(po, previousCheck);
    }
}

void PDynamicsHandler::resolve_particle_collision_against_other(ParticleObject po, Particle *hitParticle,
                                                                px::Vec2i currentCheck,
                                                                px::Vec2i previousCheck, float dt)
{
    px::Vec2i hitDirection = currentCheck - previousCheck;

    px::VerletBody &verletA = po.particle->getVerlet();
    px::VerletBody &verletB = hitParticle->getVerlet();

    px::Vec2f velA = verletA.getVelocity(dt);
    px::Vec2f velB = verletB.getVelocity(dt);

    float restitution = std::min(po.particle->getRestitution(), hitParticle->getRestitution());

    px::Vec2f newVelA = velA;
    px::Vec2f newVelB = velB;

    float mA = po.particle->getMass();
    float mB = hitParticle->getMass();

    if (hitDirection.x != 0)
    {
        newVelA.x = px::Physics::elasticCollisionVelocityA(mA, mB, velA.x, velB.x) * restitution;
        newVelB.x = px::Physics::elasticCollisionVelocityB(mA, mB, velA.x, velB.x) * restitution;
    }
    if (hitDirection.y != 0)
    {
        newVelA.y = px::Physics::elasticCollisionVelocityA(mA, mB, velA.y, velB.y) * restitution;
        newVelB.y = px::Physics::elasticCollisionVelocityB(mA, mB, velA.y, velB.y) * restitution;
    }

    constexpr float threshold = 0.25f;
    if (std::abs(newVelA.x) < threshold)
    {
        newVelA.x = 0.0f;
    }
    if (std::abs(newVelA.y) < threshold)
    {
        newVelA.y = 0.0f;
    }
    if (std::abs(newVelB.x) < threshold)
    {
        newVelB.x = 0.0f;
    }
    if (std::abs(newVelB.y) < threshold)
    {
        newVelB.y = 0.0f;
    }

    verletA.setPosition(previousCheck.toFloat());
    verletA.setVelocity(newVelA, dt);
    verletB.setVelocity(newVelB, dt);
}

void PDynamicsHandler::resolve_particle_collision_against_null(ParticleObject po, px::Vec2i previousCheck)
{
    po.particle->getVerlet().setPosition(previousCheck.toFloat());
}
