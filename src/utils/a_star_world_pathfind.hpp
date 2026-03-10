#pragma once

#include "a_star.hpp"
#include "types/data_structures/chunk_map.hpp"
#include "world/particle/particle.hpp"

class AStarWorld : public AStarSystem
{
  public:
    AStarWorld(ChunkMap<Particle> &particles) : r_particles(particles) {}
    bool isNeighborWalkable(int x, int y) override
    {
        if (Particle *p = r_particles.get(x, y))
        {
            return !p->isSolid() || p->isMoving();
        }
        else
        {
            return true;
        }
    }

  private:
    ChunkMap<Particle> &r_particles;
};
