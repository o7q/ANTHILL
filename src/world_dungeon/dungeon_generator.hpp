#pragma once

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/vec.hpp"

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

    void generate_convert_rooms_to_graph(NodeGraph<Vec2i>& graphOut);

  private:
    Rectangle_i m_bounds;

    Vec2i m_minRoomSize = {10,10};
    Vec2i m_maxRoomSize = {20, 20};

    int m_roomCount              = 100;
    int m_roomSeparateIterations = 10;
    int m_roomMinSpacing         = 0;
    int m_roomMaxSpacing         = 100;
};
