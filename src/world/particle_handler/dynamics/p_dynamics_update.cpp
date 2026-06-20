#include "p_dynamics_handler.hpp"

#include "px/basic_types/rectangle.hpp"
#include "px/verlet/verlet.hpp"
#include "world/particle_handler/particle.hpp"
#include <limits>

void PDynamicsHandler::update(px::TimeHandler::Info timeInfo, px::Vec2i origin)
{
    px::Vec2i lastNavmeshChunkIndex = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};

    px::Rectangle_i updateRect(origin, m_updateSize);
    px::Vec2i a = updateRect.getA();
    px::Vec2i b = updateRect.getB();

    for (int y = b.y; y >= a.y; --y)
    {
        for (int x = b.x; x >= a.x; --x)
        {
            px::Vec2i pos               = {x, y};
            Particle *p                 = r_particles.get(pos);
            const uint8_t *swapStatePtr = m_swapStates.get(pos);
            uint8_t swapState           = 0;
            if (swapStatePtr)
            {
                swapState = *swapStatePtr;
            }
            else
            {
                m_swapStates.set(pos, 0);
            }

            if (!p)
            {
                continue;
            }

            px::Vec2i chunkIndex = r_navmesh.getIndexFromWorldPosition(pos);
            if (chunkIndex != lastNavmeshChunkIndex)
            {
                r_navmesh.resetChunk(chunkIndex);
            }
            r_navmesh.update(p, chunkIndex);
            lastNavmeshChunkIndex = chunkIndex;
            if (swapState == m_globalSwapState || p->getPhysicsType() == Particle::PhysicsType::None)
            {
                continue;
            }

            ParticleObject po{p, pos};
            update_particle(po, timeInfo.dt);
        }
    }

    m_globalSwapState = ~m_globalSwapState;
}

void PDynamicsHandler::update_particle(ParticleObject po, float dt)
{
    switch (po.particle->getPhysicsType())
    {
    case Particle::PhysicsType::Sand:
        update_sand_particle(po, dt);
        break;
    case Particle::PhysicsType::Sandstone:
        update_sandstone_particle(po, dt);
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

void PDynamicsHandler::finalize_particle(ParticleObject po)
{
    px::Vec2i finalPos = po.particle->getVerlet().getPosition().toGrid();
    m_swapStates.set(finalPos, m_globalSwapState);
    r_particles.move(po.pos, finalPos);
}
