#include "navmesh.hpp"

void Navmesh::update(const Particle *p, px::Vec2i index)
{
    if (p->isAir() || p->isMoving())
    {
        return;
    }

    ChunkData *data = &m_mesh[index];
    if (p->isSolid())
    {
        data->containsSolid = true;
    }
}

void Navmesh::resetChunk(px::Vec2i index) { m_mesh[index] = ChunkData(); }

const Navmesh::ChunkData *Navmesh::getChunkDataFromIndex(px::Vec2i index) const
{
    auto it = m_mesh.find(index);
    if (it == m_mesh.end())
    {
        return nullptr;
    }
    return &it->second;
}

px::Vec2i Navmesh::getIndexFromWorldPosition(px::Vec2i pos) const
{
    return (pos.toFloat() / m_resolution.toFloat()).toGrid();
}
