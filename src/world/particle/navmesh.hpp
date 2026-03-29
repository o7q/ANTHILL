#pragma once

#include "utils/data_structures/index_2d.hpp"
#include "world/particle/particle.hpp"
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

    void resetChunk(Index2D index) { m_mesh[index] = ChunkData(); }

    void update(const Particle *p, Index2D index)
    {
        if (p->isAir())
        {
            return;
        }

        ChunkData *data = &m_mesh[index];
        if (p->isSolid())
        {
            data->containsSolid = true;
        }
    }

    const ChunkData *getChunkFromIndex(Index2D index) const
    {
        auto it = m_mesh.find(index);
        if (it == m_mesh.end())
        {
            return nullptr;
        }
        return &it->second;
    }

    Index2D getIndexFromWorldPosition(Vec2i pos) const
    {
        int cw = static_cast<int>(m_resolution.x);
        int ch = static_cast<int>(m_resolution.y);

        int chunk_x = pos.x / cw - (pos.x % cw < 0);
        int chunk_y = pos.y / ch - (pos.y % ch < 0);
        return Index2D(chunk_x, chunk_y);
    }

    Vec2u getResolution() const { return m_resolution; }

  private:
    std::unordered_map<Index2D, ChunkData, Index2DHash> m_mesh;
    Vec2u m_resolution;
};
