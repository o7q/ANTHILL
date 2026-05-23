#pragma once

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/vec.hpp"

class Room
{
  public:
  private:
    Vec2i m_size;
};

class DungeonGenerator
{
  public:
    DungeonGenerator();

    NodeGraph<Vec2i> generate();

    Rectangle_i getBounds() const { return m_bounds; }

  private:
    void generate_place_rooms(std::vector<Rectangle_i> &roomsOut);
    void generate_fix_room_intersection(std::vector<Rectangle_i> &roomsOut);
    void generate_purge_bad_rooms(std::vector<Rectangle_i> &roomsOut);

    void generate_convert_rooms_to_graph(NodeGraph<Vec2i> &graphOut);

  private:
    Rectangle_i m_bounds;

    Vec2i m_minRoomSize = {120, 120};
    Vec2i m_maxRoomSize = {200, 200};

    Vec2i m_minRoomPositionBias = {-20, -20};
    Vec2i m_maxRoomPositionBias = {20, 20};

    int m_initialRoomPlacementCount    = 100;
    int m_roomMinSpacing               = 100;
    int m_roomMaxSpacing               = 500;
    const int m_roomSeparateIterations = 10;
};
