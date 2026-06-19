#pragma once

#include "px/data_structures/chunk_map.hpp"
#include "px/math/geometry/rectangle.hpp"
#include "px/math/geometry/vec.hpp"
#include "world_generator/spawn_data.hpp"
#include <string>
#include <unordered_map>

class Room
{
  public:
    Room() : m_data({32, 32}) {}
    Room(Vec2i size) : m_data({32, 32}) { m_size = size; }

    virtual void writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const {}
    const std::unordered_map<RectangleSide, int> &getConnectionPoints() const { return m_connectionPoints; }
    Vec2i getSize() const { return m_size; }

  protected:
    struct InitConfig
    {
        std::string colorPath                  = "";
        std::string lookupPath                 = "";
        std::string backgroundPath             = "";
    };

    void init(InitConfig config);
    void init(Vec2i size) { m_size = size; }

    ChunkMap<StructurePositionalSpawnData> m_data;
    std::unordered_map<RectangleSide, int> m_connectionPoints;

  private:
    Vec2i m_size;
};
