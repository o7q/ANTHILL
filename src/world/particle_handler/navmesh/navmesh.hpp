#pragma once

#include "px/math/geometry/vec.hpp"
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

    void update(const Particle *p, Vec2i index);
    void resetChunk(Vec2i index);
    const ChunkData *getChunkDataFromIndex(Vec2i index) const;
    Vec2i getIndexFromWorldPosition(Vec2i pos) const;
    Vec2u getResolution() const { return m_resolution; }

  private:
    std::unordered_map<Vec2i, ChunkData, Vec2Hash<int>> m_mesh;
    Vec2u m_resolution;
};
