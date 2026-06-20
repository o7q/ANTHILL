#pragma once

#include "px/basic_types/vec.hpp"
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
    Navmesh(px::Vec2u resolution) { m_resolution = resolution; }

    void update(const Particle *p, px::Vec2i index);
    void resetChunk(px::Vec2i index);
    const ChunkData *getChunkDataFromIndex(px::Vec2i index) const;
    px::Vec2i getIndexFromWorldPosition(px::Vec2i pos) const;
    px::Vec2u getResolution() const { return m_resolution; }

  private:
    std::unordered_map<px::Vec2i, ChunkData, px::Vec2Hash<int>> m_mesh;
    px::Vec2u m_resolution;
};
