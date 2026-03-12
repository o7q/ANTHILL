#pragma once

#include "a_star.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/particle/particle.hpp"

class AStarWorldSolver : public AStarSolver
{
  public:
    AStarWorldSolver(ChunkMap<Particle> &particles) : r_particles(particles) {}
    bool isNeighborWalkable(int x, int y) override
    {
        if (Particle *p = r_particles.get(x, y))
        {
            if (!p->isSolid() || p->isMoving())
            {
                return true;
            }
        }

        return false;
    }

  private:
    ChunkMap<Particle> &r_particles;
};
