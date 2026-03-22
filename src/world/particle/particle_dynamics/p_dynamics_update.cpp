#include "p_dynamics_handler.hpp"

#include "math/line.hpp"
#include "math/physics/utils.hpp"
#include "math/physics/verlet.hpp"
#include "world/particle/particle.hpp"
#include <algorithm>

void PDynamicsHandler::update(float dt)
{
    const Vec2u chunkSize = r_particles.getChunkSize();

    for (auto &[chunkPos, chunk] : r_particles.getChunks())
    {
        int originChunkX = static_cast<int>(std::floor(
            m_updateChunksOrigin.x / static_cast<float>(chunkSize.x)));
        int originChunkY = static_cast<int>(std::floor(
            m_updateChunksOrigin.y / static_cast<float>(chunkSize.y)));

        int chunkXDist = chunkPos.x - originChunkX;
        int chunkYDist = chunkPos.y - originChunkY;

        if (chunkXDist * chunkXDist + chunkYDist * chunkYDist >=
            m_updateChunksRadius * m_updateChunksRadius)
        {
            continue;
        }

        int innerBaseX = chunkPos.x * chunkSize.x;
        int innerBaseY = chunkPos.y * chunkSize.y;
        for (int y = chunkSize.y - 1; y >= 0; --y)
        {
            for (int x = chunkSize.x - 1; x >= 0; --x)
            {
                int px = innerBaseX + x;
                int py = innerBaseY + y;

                if (Particle *p = r_particles.get(px, py))
                {
                    if (p->getUpdateSwapID() == m_updateSwapID || p->isAir() ||
                        p->isImmovable())
                    {
                        continue;
                    }

                    ParticleObject po{p, px, py};
                    update_particle(po, dt);
                }
            }
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

    auto function = [&](int x, int y)
    {
        if (Particle *next = r_particles.get(x, y))
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
                hitCell = Vec2i(x, y);
                hitParticle = next;
                return true;
            }
        }

        previousCheck = Vec2i(x, y);
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

    verletA.setPosition(previousCheck.x, previousCheck.y);
    verletA.setVelocity(newVelA.x, newVelA.y, dt);
    verletB.setVelocity(newVelB.x, newVelB.y, dt);
}

void PDynamicsHandler::finalize_particle(ParticleObject po)
{
    Vec2i finalPos = po.particle->getVerlet().getPosition().toGrid();

    po.particle->setUpdateSwapID(m_updateSwapID);
    r_particles.move(po.x, po.y, finalPos.x, finalPos.y);
}
