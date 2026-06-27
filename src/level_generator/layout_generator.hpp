#pragma once

#include "px/basic_types/rectangle.hpp"
#include "px/basic_types/vec.hpp"
#include "px/data_structures/node_graph.hpp"
#include "px/utils/random.hpp"
#include "room/room.hpp"
#include <vector>

struct RoomPlaceholder
{
    const Room *room;
    px::Vec2i pos;
    bool special = false;
};

class LevelLayoutGenerator
{
  public:
    struct Config
    {
        px::Rectangle_i bounds;

        std::vector<px::Random::WeightedValue<const Room *>> roomPool;
        std::vector<RoomPlaceholder> specialRooms;

        px::Vec2i roomSpread = {20, 20};

        int initialRoomPlacementCount = 100;
        px::Vec2i roomMinSpacing      = {0, 0};
        int roomSeparateIterations    = 10;
    };

  public:
    px::NodeGraph<const Room *> generate(uint32_t seed);

    void setConfig(const Config &config) { m_config = config; }

  private:
    void generate_place_rooms(std::vector<RoomPlaceholder> &roomsOut, uint32_t &seed);
    void generate_fix_room_intersection(std::vector<RoomPlaceholder> &roomsOut, uint32_t &seed);
    void generate_purge_bad_rooms(std::vector<RoomPlaceholder> &roomsOut);

    void generate_convert_rooms_to_graph(px::NodeGraph<px::Vec2i> &graphOut);

  private:
    Config m_config;
};
