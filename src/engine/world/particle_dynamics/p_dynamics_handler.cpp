#include "p_dynamics_handler.hpp"

#include "engine/backend/utils/math.hpp"
#include "engine/math/verlet.hpp"
#include "engine/world/particle.hpp"
#include <algorithm>

void PDynamicsHandler::update(float dt)
{
    const Vec2<unsigned int> chunkSize = r_particles.getChunkSize();

    for (auto &[chunkPos, chunk] : r_particles.getChunks())
    {
        int originChunkX = std::floor(m_updateChunksOrigin.x /
                                      static_cast<float>(chunkSize.x));
        int originChunkY = std::floor(m_updateChunksOrigin.y /
                                      static_cast<float>(chunkSize.y));

        int chunkXDist = chunkPos.first - originChunkX;
        int chunkYDist = chunkPos.second - originChunkY;

        if (chunkXDist * chunkXDist + chunkYDist * chunkYDist >=
            m_updateChunksRadius * m_updateChunksRadius)
        {
            continue;
        }

        int innerBaseX = chunkPos.first * chunkSize.x;
        int innerBaseY = chunkPos.second * chunkSize.y;
        for (int y = chunkSize.y - 1; y >= 0; --y)
        {
            for (int x = chunkSize.x - 1; x >= 0; --x)
            {
                int px = innerBaseX + x;
                int py = innerBaseY + y;

                if (Particle *p = r_particles.get(px, py))
                {
                    if (p->getUpdateSwapID() == m_updateSwapID || p->isAir())
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
                                                  Vec2<float> start,
                                                  Vec2<float> end, float dt)
{
    Vec2<int> previousCheck{};
    Vec2<int> hitCell{};
    Particle *hitParticle = nullptr;
    bool hit = false;

    auto function = [&](int x, int y)
    {
        if (Particle *next = r_particles.get(x, y))
        {
            bool canPass = false;

            if ((po.particle->isSolid() || po.particle->isLiquid()) &&
                next->isGas())
            {
                canPass = true;
            }

            if ((po.particle->isGas()) && next->isAir())
            {
                canPass = true;
            }

            if (!canPass && next != po.particle)
            {
                hit = true;
                hitCell = Vec2<int>(x, y);
                hitParticle = next;
                return false;
            }
        }

        previousCheck = Vec2<int>(x, y);
        return true;
    };
    BackendUtils::Math::bresenhamLine(
        Vec2<int>(std::floor(start.x), std::floor(start.y)),
        Vec2<int>(std::floor(end.x), std::floor(end.y)), function);

    if (!hit)
    {
        return;
    }

    VerletBody &verletA = po.particle->getVerlet();
    VerletBody &verletB = hitParticle->getVerlet();

    Vec2<float> velA = verletA.getVelocity(dt);
    Vec2<float> velB = verletB.getVelocity(dt);

    float restitution =
        std::min(po.particle->getRestitution(), hitParticle->getRestitution());

    Vec2<int> hitDirection = hitCell - previousCheck;

    Vec2<float> newVelA = velA;
    Vec2<float> newVelB = velB;

    float mA = verletA.getMass();
    float mB = verletB.getMass();
    float totalMass = mA + mB;

    if (hitDirection.x != 0)
    {
        newVelA.x =
            ((mA - mB) / totalMass * velA.x + (2 * mB) / totalMass * velB.x) *
            restitution;
        newVelB.x =
            ((mB - mA) / totalMass * velB.x + (2 * mA) / totalMass * velA.x) *
            restitution;
    }
    if (hitDirection.y != 0)
    {
        newVelA.y =
            ((mA - mB) / totalMass * velA.y + (2 * mB) / totalMass * velB.y) *
            restitution;
        newVelB.y =
            ((mB - mA) / totalMass * velB.y + (2 * mA) / totalMass * velA.y) *
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
    Vec2<float> finalPos = po.particle->getVerlet().getPosition();

    int finalX = static_cast<int>(std::floor(finalPos.x));
    int finalY = static_cast<int>(std::floor(finalPos.y));

    po.particle->setUpdateSwapID(m_updateSwapID);
    r_particles.move(po.x, po.y, finalX, finalY);
}
