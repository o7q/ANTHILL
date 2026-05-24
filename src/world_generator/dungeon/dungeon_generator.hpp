#pragma once

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/vec.hpp"

class Room
{
  public:
    void setSize(Vec2i size) { m_size = size; }
    Vec2i getSize() const { return m_size; }

  private:
    Vec2i m_size;
};

class DungeonGenerator
{
  public:
    DungeonGenerator() {}

    NodeGraph<Vec2i> generate(Rectangle_i bounds);

  private:
    void generate_place_rooms(std::vector<Rectangle_i> &roomsOut, Rectangle_i bounds);
    void generate_fix_room_intersection(std::vector<Rectangle_i> &roomsOut);
    void generate_purge_bad_rooms(std::vector<Rectangle_i> &roomsOut, Rectangle_i bounds);

    void generate_convert_rooms_to_graph(NodeGraph<Vec2i> &graphOut);

  private:
    Vec2i m_minRoomSize = {10, 10};
    Vec2i m_maxRoomSize = {20, 20};

    Vec2i m_minRoomPositionBias = {-20, -20};
    Vec2i m_maxRoomPositionBias = {20, 20};

    int m_initialRoomPlacementCount    = 1000;
    Vec2i m_roomMinSpacing             = {0, 0};
    Vec2i m_roomMaxSpacing             = {500, 500};
    const int m_roomSeparateIterations = 10;
};
