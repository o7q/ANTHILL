#pragma once

#include "utils/data_structures/index_2d.hpp"
#include "world/particle/particle.hpp"
#include <optional>
#include <unordered_map>

class Navmesh
{
  public:
    struct ChunkData
    {
        bool containsSolid = false;
    };

  public:
    Navmesh(Vec2u resolution) : m_mesh() { m_resolution = resolution; }

    void destroy() { m_mesh.clear(); }

    void update(Particle p, int x, int y)
    {
        Index2D index = getChunkIndex(x, y);

        ChunkData *data = &m_mesh[index];

        if (p.isSolid())
        {
            data->containsSolid = true;
        }
    }

    const std::unordered_map<Index2D, ChunkData, Index2DHash> &getMesh() const
    {
        return m_mesh;
    }
    Vec2u getResolution() const { return m_resolution; }

    const std::optional<ChunkData> getChunk(Index2D index) const
    {
        if (m_mesh.find(index) == m_mesh.end())
        {
            return std::nullopt;
        }
        return m_mesh.at(index);
    }

    Index2D getChunkIndex(int x, int y) const
    {
        int cw = static_cast<int>(m_resolution.x);
        int ch = static_cast<int>(m_resolution.y);

        int chunk_x = x / cw - (x % cw < 0);
        int chunk_y = y / ch - (y % ch < 0);

        return Index2D(chunk_x, chunk_y);
    }

  private:
    std::unordered_map<Index2D, ChunkData, Index2DHash> m_mesh;
    Vec2u m_resolution;
};
