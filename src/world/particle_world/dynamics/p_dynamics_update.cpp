#include "p_dynamics_handler.hpp"

#include "math/physics/verlet.hpp"
#include "world/particle_world/particle.hpp"
#include <limits>

void PDynamicsHandler::update(float dt, Vec2i origin)
{
    Index2D lastNavmeshChunkIndex(std::numeric_limits<int>::max(),
                                  std::numeric_limits<int>::max());

    for (int y = origin.y + static_cast<int>(m_updateRadius.y);
         y >= origin.y - static_cast<int>(m_updateRadius.y); --y)
    {
        for (int x = origin.x + static_cast<int>(m_updateRadius.x);
             x >= origin.x - static_cast<int>(m_updateRadius.x); --x)
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
                p->getPhysicsType() == Particle::PhysicsType::None)
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

void PDynamicsHandler::finalize_particle(ParticleObject po)
{
    Vec2i finalPos = po.particle->getVerlet().getPosition().toGrid();

    po.particle->setUpdateSwapID(m_updateSwapID);
    r_particles.move(po.pos, finalPos);
}
