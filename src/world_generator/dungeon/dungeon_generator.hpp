#pragma once

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/vec.hpp"
#include "core/math/random.hpp"
#include <vector>

class Room
{
  public:
    Room() = default;
    Room(Vec2i size) { m_size = size; }

    Vec2i getSize() const { return m_size; }

  private:
    Vec2i m_size;
};

struct PositionedRoom
{
    Room room;
    Vec2i pos;
};

class DungeonGenerator
{
  public:
    DungeonGenerator()
    {
        m_roomPool.push_back({Room({100, 100}), 10});
        m_roomPool.push_back({Room({200, 200}), 1});
    };

    NodeGraph<Room> generate(Rectangle_i bounds);

  private:
    void generate_place_rooms(std::vector<PositionedRoom> &roomsOut, Rectangle_i bounds);
    void generate_fix_room_intersection(std::vector<PositionedRoom> &roomsOut);
    void generate_purge_bad_rooms(std::vector<PositionedRoom> &roomsOut, Rectangle_i bounds);

    void generate_convert_rooms_to_graph(NodeGraph<Vec2i> &graphOut);

  private:
    std::vector<Math::Random::WeightedValue<Room>> m_roomPool;

    Vec2i m_minRoomPositionBias = {-20, -20};
    Vec2i m_maxRoomPositionBias = {20, 20};

    int m_initialRoomPlacementCount    = 1000;
    Vec2i m_roomMinSpacing             = {0, 0};
    Vec2i m_roomMaxSpacing             = {500, 500};
    const int m_roomSeparateIterations = 10;
};
