#pragma once

#include "px/data_structures/node_graph.hpp"
#include "px/math/geometry/rectangle.hpp"
#include "px/math/geometry/vec.hpp"
#include "px/math/random.hpp"
#include "room/room.hpp"
#include <vector>

struct RoomPlaceholder
{
    const Room *room;
    Vec2i pos;
    bool special = false;
};

class LevelLayoutGenerator
{
  public:
    struct Config
    {
        Rectangle_i bounds;

        std::vector<Math::Random::WeightedValue<const Room *>> roomPool;
        std::vector<RoomPlaceholder> specialRooms;

        Vec2i roomSpread = {20, 20};

        int initialRoomPlacementCount = 100;
        Vec2i roomMinSpacing          = {0, 0};
        int roomSeparateIterations    = 10;
    };

  public:
    NodeGraph<const Room *> generate(uint32_t seed);

    void setConfig(const Config &config) { m_config = config; }

  private:
    void generate_place_rooms(std::vector<RoomPlaceholder> &roomsOut, uint32_t &seed);
    void generate_fix_room_intersection(std::vector<RoomPlaceholder> &roomsOut, uint32_t &seed);
    void generate_purge_bad_rooms(std::vector<RoomPlaceholder> &roomsOut);

    void generate_convert_rooms_to_graph(NodeGraph<Vec2i> &graphOut);

  private:
    Config m_config;
};
