#pragma once

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/vec.hpp"

class DungeonGenerator
{
  public:
    DungeonGenerator();

    void generate();

    Rectangle_i getBounds() const { return m_bounds; }
    const NodeGraph<Vec2i> &getRoomGraph() const { return m_roomGraph; }

  private:
    void generate_place_rooms();
    void generate_fix_room_intersection();
    void generate_purge_bad_rooms();

  private:
    Rectangle_i m_bounds;
    NodeGraph<Vec2i> m_roomGraph;

    Vec2i m_minRoomSize = {10, 10};
    Vec2i m_maxRoomSize = {20, 20};

    int m_roomCount              = 10;
    int m_roomSeparateIterations = 10;
    int m_roomMinSpacing         = 0;
    int m_roomMaxSpacing         = 30;
};
