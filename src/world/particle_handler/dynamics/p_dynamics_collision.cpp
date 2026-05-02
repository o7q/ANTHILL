#include "p_dynamics_handler.hpp"

#include "math/line.hpp"
#include "math/physics.hpp"

void PDynamicsHandler::handle_particle_trajectory(ParticleObject po, Vec2f start, Vec2f end, float dt)
{
    Vec2i currentCheck    = start.toGrid();
    Vec2i previousCheck   = start.toGrid();
    Particle *hitParticle = nullptr;
    bool hit              = false;

    auto function = [&](Vec2i pos)
    {
        currentCheck = pos;

        Particle *next = r_particles.get(pos);

        if (next == po.particle)
        {
            return false;
        }

        if (!next)
        {
            hit         = true;
            hitParticle = next;
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

    Math::Line::bresenhamLine(start.toGrid(), end.toGrid(), function);

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
                                                                Vec2i currentCheck, Vec2i previousCheck,
                                                                float dt)
{
    Vec2i hitDirection = currentCheck - previousCheck;

    VerletBody &verletA = po.particle->getVerlet();
    VerletBody &verletB = hitParticle->getVerlet();

    Vec2f velA = verletA.getVelocity(dt);
    Vec2f velB = verletB.getVelocity(dt);

    float restitution = std::min(po.particle->getRestitution(), hitParticle->getRestitution());

    Vec2f newVelA = velA;
    Vec2f newVelB = velB;

    float mA = po.particle->getMass();
    float mB = hitParticle->getMass();

    if (hitDirection.x != 0)
    {
        newVelA.x = Utils::Math::Physics::elasticCollisionVelocityA(mA, mB, velA.x, velB.x) * restitution;
        newVelB.x = Utils::Math::Physics::elasticCollisionVelocityB(mA, mB, velA.x, velB.x) * restitution;
    }
    if (hitDirection.y != 0)
    {
        newVelA.y = Utils::Math::Physics::elasticCollisionVelocityA(mA, mB, velA.y, velB.y) * restitution;
        newVelB.y = Utils::Math::Physics::elasticCollisionVelocityB(mA, mB, velA.y, velB.y) * restitution;
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

void PDynamicsHandler::resolve_particle_collision_against_null(ParticleObject po, Vec2i previousCheck)
{
    po.particle->getVerlet().setPosition(previousCheck.toFloat());
}
