#pragma once

#include "core/math/rectangle.hpp"
#include "core/math/vec.hpp"
#include <vector>

class DungeonGenerator
{
  public:
    DungeonGenerator();

    void generate();

    GridRectangle getBounds() const { return m_bounds; }
    const std::vector<GridRectangle> &getRooms() const { return m_rooms; }

  private:
    void generate_place_rooms();
    void generate_fix_room_intersection();
    void generate_purge_bad_rooms();

  private:
    GridRectangle m_bounds;
    std::vector<GridRectangle> m_rooms;

    Vec2i m_minRoomSize = {10, 10};
    Vec2i m_maxRoomSize = {20, 20};

    int m_roomCount              = 20;
    int m_roomSeparateIterations = 10;
    int m_roomMinSpacing         = 0;
    int m_roomMaxSpacing         = 10;
};
