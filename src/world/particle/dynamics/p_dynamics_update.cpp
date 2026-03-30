#include "p_dynamics_handler.hpp"

#include "math/line.hpp"
#include "math/physics/utils.hpp"
#include "math/physics/verlet.hpp"
#include "world/particle/particle.hpp"
#include <algorithm>

void PDynamicsHandler::update(float dt, Vec2i origin, Vec2i size)
{
    Vec2i halfSize = size / 2;

    Index2D lastNavmeshChunkIndex(1000000000, 1000000000);

    for (int y = origin.y + halfSize.y; y >= origin.y - halfSize.y; --y)
    {
        for (int x = origin.x + halfSize.x; x >= origin.x - halfSize.x; --x)
        {
            Particle *p = r_particles.get({x, y});

            if (!p)
            {
                continue;
            }

            Index2D chunkIndex = r_navmesh.getIndexFromWorldPosition({x, y});
            if (chunkIndex != lastNavmeshChunkIndex)
            {
                r_navmesh.resetChunk(chunkIndex);
            }
            r_navmesh.update(p, chunkIndex);
            lastNavmeshChunkIndex = chunkIndex;
            if (p->getUpdateSwapID() == m_updateSwapID || p->isAir() ||
                p->isImmovable())
            {
                continue;
            }

            ParticleObject po{p, {x, y}};
            update_particle(po, dt);
        }
    }

    m_updateSwapID = !m_updateSwapID;
}

void PDynamicsHandler::update_particle(ParticleObject po, float dt)
{
    switch (po.particle->getPhysicsType())
    {
    case Particle::PhysicsType::Sand:
        update_sand_particle(po, dt);
        break;
    case Particle::PhysicsType::Water:
        update_water_particle(po, dt);
        break;
    case Particle::PhysicsType::Smoke:
        update_smoke_particle(po, dt);
        break;
    default:
        break;
    }
}

void PDynamicsHandler::resolve_particle_collision(ParticleObject po,
                                                  Vec2f start, Vec2f end,
                                                  float dt)
{
    Vec2i previousCheck = start.toGrid();
    Vec2i hitCell{};
    Particle *hitParticle = nullptr;
    bool hit = false;

    auto function = [&](Vec2i pos)
    {
        if (Particle *next = r_particles.get(pos))
        {
            bool canPass = false;

            if (po.particle->isSolid() && can_solid_occupy(next))
            {
                canPass = true;
            }

            if (po.particle->isLiquid() && can_liquid_occupy(next))
            {
                canPass = true;
            }

            if (po.particle->isGas() && can_gas_occupy(next))
            {
                canPass = true;
            }

            if (!canPass && next != po.particle)
            {
                hit = true;
                hitCell = pos;
                hitParticle = next;
                return true;
            }
        }

        previousCheck = pos;
        return false;
    };

    Math::Line::bresenhamLine(start.toGrid(), end.toGrid(), function);

    if (!hit)
    {
        return;
    }

    VerletBody &verletA = po.particle->getVerlet();
    VerletBody &verletB = hitParticle->getVerlet();

    Vec2f velA = verletA.getVelocity(dt);
    Vec2f velB = verletB.getVelocity(dt);

    float restitution =
        std::min(po.particle->getRestitution(), hitParticle->getRestitution());

    Vec2i hitDirection = hitCell - previousCheck;

    Vec2f newVelA = velA;
    Vec2f newVelB = velB;

    float mA = verletA.getMass();
    float mB = verletB.getMass();

    if (hitDirection.x != 0)
    {
        newVelA.x = Utils::Math::Physics::elasticCollisionVelocityA(
                        mA, mB, velA.x, velB.x) *
                    restitution;
        newVelB.x = Utils::Math::Physics::elasticCollisionVelocityB(
                        mA, mB, velA.x, velB.x) *
                    restitution;
    }
    if (hitDirection.y != 0)
    {
        newVelA.y = Utils::Math::Physics::elasticCollisionVelocityA(
                        mA, mB, velA.y, velB.y) *
                    restitution;
        newVelB.y = Utils::Math::Physics::elasticCollisionVelocityB(
                        mA, mB, velA.y, velB.y) *
                    restitution;
    }

    const float threshold = 0.05f;
    if (std::abs(newVelA.x) < threshold)
    {
        newVelA.x = 0;
    }
    if (std::abs(newVelA.y) < threshold)
    {
        newVelA.y = 0;
    }
    if (std::abs(newVelB.x) < threshold)
    {
        newVelB.x = 0;
    }
    if (std::abs(newVelB.y) < threshold)
    {
        newVelB.y = 0;
    }

    verletA.setPosition(previousCheck.toFloat());
    verletA.setVelocity(newVelA, dt);
    verletB.setVelocity(newVelB, dt);
}

void PDynamicsHandler::finalize_particle(ParticleObject po)
{
    Vec2i finalPos = po.particle->getVerlet().getPosition().toGrid();

    po.particle->setUpdateSwapID(m_updateSwapID);
    r_particles.move(po.pos, finalPos);
}
