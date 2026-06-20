#pragma once

#include "px/basic_types/rectangle.hpp"
#include "px/basic_types/vec.hpp"
#include "px/data_structures/chunk_map.hpp"
#include "world_generator/spawn_data.hpp"
#include <string>
#include <unordered_map>

class Room
{
  public:
    Room() : m_data({32, 32}) {}
    Room(px::Vec2i size) : m_data({32, 32}) { m_size = size; }

    virtual void writeToLayer(px::Vec2i worldTopLeft,
                              px::ChunkMap<StructurePositionalSpawnData> &dataOut) const
    {
    }
    const std::unordered_map<px::RectangleSide, int> &getConnectionPoints() const
    {
        return m_connectionPoints;
    }
    px::Vec2i getSize() const { return m_size; }

  protected:
    struct InitConfig
    {
        std::string colorPath      = "";
        std::string lookupPath     = "";
        std::string backgroundPath = "";
    };

    void init(InitConfig config);
    void init(px::Vec2i size) { m_size = size; }

    px::ChunkMap<StructurePositionalSpawnData> m_data;
    std::unordered_map<px::RectangleSide, int> m_connectionPoints;

  private:
    px::Vec2i m_size;
};
