#pragma once

#include "core/utils/data_structures/index_2d.hpp"
#include "world/particle_handler/particle.hpp"
#include <unordered_map>

class Navmesh
{
  public:
    struct ChunkData
    {
        bool containsSolid = false;
    };

  public:
    Navmesh(Vec2u resolution) { m_resolution = resolution; }

    void update(const Particle *p, Index2D index);
    void resetChunk(Index2D index);
    const ChunkData *getChunkFromIndex(Index2D index) const;
    Index2D getIndexFromWorldPosition(Vec2i pos) const;
    Vec2u getResolution() const { return m_resolution; }

  private:
    std::unordered_map<Index2D, ChunkData, Index2DHash> m_mesh;
    Vec2u m_resolution;
};
