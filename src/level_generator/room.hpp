#pragma once

#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/vec.hpp"
#include "world_generator/spawn_data.hpp"
#include <string>
#include <unordered_map>

class Room
{
  public:
    Room() = default;

    Vec2i getSize() const { return m_size; }
    const std::unordered_map<Vec2i, PositionalSpawnData, Vec2Hash<int>> &getData() const { return m_data; }
    const std::unordered_map<RectangleSide, int> &getConnectionPoints() const { return m_connectionPoints; }

  protected:
    struct InitConfig
    {
        std::string backgroundPath     = "";
        std::string particleColorPath  = "";
        std::string particleLookupPath = "";
    };

    void init(InitConfig config);
    void init(Vec2i size) { m_size = size; }

    std::unordered_map<Vec2i, PositionalSpawnData, Vec2Hash<int>> m_data;
    std::unordered_map<RectangleSide, int> m_connectionPoints;

  private:
    Vec2i m_size;
};
