
#include "dungeon_generator.hpp"
#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/triangle.hpp"
#include "core/math/graph.hpp"
#include "core/math/mesh.hpp"
#include "core/math/random.hpp"
#include <vector>

NodeGraph<Room> DungeonGenerator::generate(Rectangle_i bounds)
{
    std::vector<PositionedRoom> rooms;
    generate_place_rooms(rooms, bounds);
    generate_fix_room_intersection(rooms);
    generate_purge_bad_rooms(rooms, bounds);

    NodeGraph<Room> roomGraph;
    std::vector<Vec2i> roomPositions;
    roomPositions.reserve(rooms.size());
    for (PositionedRoom room : rooms)
    {
        Node<Room> roomNode;
        roomNode.value = room.room;
        roomGraph.set(room.pos, roomNode);

        roomPositions.push_back(room.pos);
    }

    std::vector<Triangle_i> triangulation = Math::Mesh::generateTriangulation(roomPositions);
    Math::Graph::connectNodesFromTriangulation(triangulation, roomGraph);
    roomGraph = Math::Graph::minimumSpanningTree(roomGraph);

    return roomGraph;
}

void DungeonGenerator::generate_place_rooms(std::vector<PositionedRoom> &roomsOut, Rectangle_i bounds)
{
    for (int i = 0; i < m_initialRoomPlacementCount; ++i)
    {
        int biasX = Math::Random::unseededRandomInt(m_minRoomPositionBias.x, m_maxRoomPositionBias.x);
        int biasY = Math::Random::unseededRandomInt(m_minRoomPositionBias.y, m_maxRoomPositionBias.y);

        Room room = Math::Random::weightedSelect(m_roomPool);
        Vec2i pos = {bounds.getPosition().x + biasX, bounds.getPosition().y + biasY};
        roomsOut.push_back({room, pos});
    }
}

void DungeonGenerator::generate_fix_room_intersection(std::vector<PositionedRoom> &roomsOut)
{
    for (int i = 0; i < m_roomSeparateIterations; ++i)
    {
        for (size_t j = 0; j < roomsOut.size(); ++j)
        {
            PositionedRoom &room_a = roomsOut[j];
            Rectangle_i dummy_rect_a(room_a.pos, room_a.room.getSize());
            for (size_t k = 0; k < roomsOut.size(); ++k)
            {
                if (j == k)
                {
                    continue;
                }

                PositionedRoom room_b = roomsOut[k];
                Rectangle_i dummy_rect_b(room_b.pos, room_b.room.getSize());

                Rectangle_i::OverlapResult result = dummy_rect_a.overlapping(dummy_rect_b);
                if (result.overlapping)
                {
                    int randomOffsetX =
                        Math::Random::unseededRandomInt(m_roomMinSpacing.x, m_roomMaxSpacing.x);
                    int randomOffsetY =
                        Math::Random::unseededRandomInt(m_roomMinSpacing.y, m_roomMaxSpacing.y);
                    if (result.amount.x < result.amount.y)
                    {
                        int pushX = (result.amount.x + randomOffsetX) * -result.direction.x;
                        dummy_rect_a.move({pushX, 0});
                    }
                    else
                    {
                        int pushY = (result.amount.y + randomOffsetY) * -result.direction.y;
                        dummy_rect_a.move({0, pushY});
                    }
                }
            }

            room_a.pos = dummy_rect_a.getPosition();
        }
    }
}

void DungeonGenerator::generate_purge_bad_rooms(std::vector<PositionedRoom> &roomsOut, Rectangle_i bounds)
{
    size_t current = 0;
    for (auto it = roomsOut.begin(); it != roomsOut.end();)
    {
        Rectangle_i dummy_rect_a(it->pos, it->room.getSize());

        bool purge = false;
        for (size_t i = 0; i < roomsOut.size(); ++i)
        {
            if (i == current)
            {
                continue;
            }

            PositionedRoom room_b = roomsOut[i];
            Rectangle_i dummy_rect_b(room_b.pos, room_b.room.getSize());

            if (dummy_rect_a.overlapping(dummy_rect_b).overlapping || !bounds.contains(dummy_rect_a, true))
            {
                purge = true;
                break;
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
