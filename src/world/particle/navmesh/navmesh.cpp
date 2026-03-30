#include "navmesh.hpp"

void Navmesh::update(const Particle *p, Index2D index)
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

void Navmesh::resetChunk(Index2D index) { m_mesh[index] = ChunkData(); }

const Navmesh::ChunkData *Navmesh::getChunkFromIndex(Index2D index) const
{
    auto it = m_mesh.find(index);
    if (it == m_mesh.end())
    {
        return nullptr;
    }
    return &it->second;
}

Index2D Navmesh::getIndexFromWorldPosition(Vec2i pos) const
{
    int cw = static_cast<int>(m_resolution.x);
    int ch = static_cast<int>(m_resolution.y);

    int chunk_x = pos.x / cw - (pos.x % cw < 0);
    int chunk_y = pos.y / ch - (pos.y % ch < 0);
    return Index2D(chunk_x, chunk_y);
}
