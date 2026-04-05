#include "p_dynamics_handler.hpp"

#include "math/physics/verlet.hpp"
#include "world/particle_world/particle.hpp"

void PDynamicsHandler::update(float dt, Vec2i origin, Vec2u size)
{
    Vec2i halfSize = size.toInt() / 2;

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
