
#include "level_generator.hpp"
#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/triangle.hpp"
#include "core/math/graph.hpp"
#include "core/math/mesh.hpp"
#include "core/math/random.hpp"
#include <vector>

NodeGraph<const Room *> LevelGenerator::generate(uint32_t seed)
{
    std::vector<RoomPlaceholder> rooms;

    for (RoomPlaceholder room : m_config.specialRooms)
    {
        rooms.push_back(room);
    }

    generate_place_rooms(rooms, seed);
    generate_fix_room_intersection(rooms, seed);
    generate_purge_bad_rooms(rooms);

    NodeGraph<const Room *> roomGraph;
    std::vector<Vec2i> roomPositions;
    roomPositions.reserve(rooms.size());
    for (RoomPlaceholder room : rooms)
    {
        Node<const Room *> roomNode;
        roomNode.value = room.room;
        roomGraph.set(room.pos, roomNode);

        roomPositions.push_back(room.pos);
    }

    std::vector<Triangle_i> triangulation = Math::Mesh::generateTriangulation(roomPositions);
    Math::Graph::connectNodesFromTriangulation(triangulation, roomGraph);
    roomGraph = Math::Graph::minimumSpanningTree(roomGraph);

    return roomGraph;
}

void LevelGenerator::generate_place_rooms(std::vector<RoomPlaceholder> &roomsOut, uint32_t &seed)
{
    for (int i = 0; i < m_config.initialRoomPlacementCount; ++i)
    {
        int biasX = Math::Random::seededRandomInt(-m_config.roomSpread.x, m_config.roomSpread.x, seed++);
        int biasY = Math::Random::seededRandomInt(-m_config.roomSpread.y, m_config.roomSpread.y, seed++);

        const Room *room = Math::Random::weightedSelect(m_config.roomPool, seed++);
        Vec2i pos        = {m_config.bounds.getPosition().x + biasX, m_config.bounds.getPosition().y + biasY};
        roomsOut.push_back({room, pos});
    }
}

void LevelGenerator::generate_fix_room_intersection(std::vector<RoomPlaceholder> &roomsOut, uint32_t &seed)
{
    for (int i = 0; i < m_config.roomSeparateIterations; ++i)
    {
        for (size_t j = 0; j < roomsOut.size(); ++j)
        {
            RoomPlaceholder &room_a = roomsOut[j];

            if (room_a.special)
            {
                continue;
            }

            Rectangle_i dummy_rect_a(room_a.pos, room_a.room->getSize());
            for (size_t k = 0; k < roomsOut.size(); ++k)
            {
                if (j == k)
                {
                    continue;
                }

                RoomPlaceholder room_b = roomsOut[k];
                Rectangle_i dummy_rect_b(room_b.pos, room_b.room->getSize());

                Rectangle_i::OverlapResult result = dummy_rect_a.overlapping(dummy_rect_b);
                if (result.overlapping)
                {
                    if (result.amount.x < result.amount.y)
                    {
                        int pushX = (result.amount.x + m_config.roomMinSpacing.x) * -result.direction.x;
                        dummy_rect_a.move({pushX, 0});
                    }
                    else
                    {
                        int pushY = (result.amount.y + m_config.roomMinSpacing.y) * -result.direction.y;
                        dummy_rect_a.move({0, pushY});
                    }
                }
            }

            room_a.pos = dummy_rect_a.getPosition();
        }
    }
}

void LevelGenerator::generate_purge_bad_rooms(std::vector<RoomPlaceholder> &roomsOut)
{
    size_t current = 0;
    for (auto it = roomsOut.begin(); it != roomsOut.end();)
    {
        RoomPlaceholder room = *it;
        bool purge           = false;

        if (!room.special)
        {
            Rectangle_i dummy_rect_a(room.pos, room.room->getSize());

            for (size_t i = 0; i < roomsOut.size(); ++i)
            {
                if (i == current)
                {
                    continue;
                }

                RoomPlaceholder room_b = roomsOut[i];
                Rectangle_i dummy_rect_b(room_b.pos, room_b.room->getSize());

                Vec2i overlapping = dummy_rect_a.overlapping(dummy_rect_b).amount + m_config.roomMinSpacing;

                if ((overlapping.x > 0 && overlapping.y > 0) || !m_config.bounds.contains(dummy_rect_a, true))
                {
                    purge = true;
                    break;
                }
            }
        }

        if (purge)
        {
            it = roomsOut.erase(it);
        }
        else
        {
            current++;
            it++;
        }
    }
}
