
#include "dungeon_generator.hpp"
#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/triangle.hpp"
#include "core/math/graph.hpp"
#include "core/math/mesh.hpp"
#include "core/math/random.hpp"
#include <vector>

DungeonGenerator::DungeonGenerator()
{
    m_bounds.setPosition({100, 80});
    m_bounds.setSize({200, 160});
}

NodeGraph<Vec2i> DungeonGenerator::generate()
{
    std::vector<Rectangle_i> roomRects;
    generate_place_rooms(roomRects);
    generate_fix_room_intersection(roomRects);
    generate_purge_bad_rooms(roomRects);

    NodeGraph<Vec2i> roomGraph;
    std::vector<Vec2i> roomPositions;
    roomPositions.reserve(roomRects.size());
    for (Rectangle_i room : roomRects)
    {
        Node<Vec2i> roomNode;
        roomNode.value = room.getSize();
        roomGraph.set(room.getPosition(), roomNode);

        roomPositions.push_back(room.getPosition());
    }

    std::vector<Triangle_i> triangulation = Math::Mesh::generateTriangulation(roomPositions);
    Math::Graph::connectNodesFromTriangulation(triangulation, roomGraph);
    roomGraph = Math::Graph::minimumSpanningTree(roomGraph);

    return roomGraph;
}

void DungeonGenerator::generate_place_rooms(std::vector<Rectangle_i> &roomsOut)
{
    for (int i = 0; i < m_roomCount; ++i)
    {
        Vec2i randomInitialPos = {m_bounds.getPosition().x + Math::Random::unseededRandomInt(-20, 20),
                                  m_bounds.getPosition().y + Math::Random::unseededRandomInt(-20, 20)};

        Vec2i randomSize = {Math::Random::unseededRandomInt(m_minRoomSize.x, m_maxRoomSize.x),
                            Math::Random::unseededRandomInt(m_minRoomSize.y, m_maxRoomSize.y)};

        roomsOut.push_back(Rectangle_i(randomInitialPos, randomSize));
    }
}

void DungeonGenerator::generate_fix_room_intersection(std::vector<Rectangle_i> &roomsOut)
{
    for (int i = 0; i < m_roomSeparateIterations; ++i)
    {
        for (size_t j = 0; j < roomsOut.size(); ++j)
        {
            Rectangle_i &room_a = roomsOut[j];
            for (size_t k = 0; k < roomsOut.size(); ++k)
            {
                if (j == k)
                {
                    continue;
                }

                Rectangle_i &room_b = roomsOut[k];

                Rectangle_i::OverlapResult result = room_a.overlapping(room_b);
                if (result.overlapping)
                {
                    int randomOffset = Math::Random::unseededRandomInt(m_roomMinSpacing, m_roomMaxSpacing);
                    if (result.amount.x < result.amount.y)
                    {
                        room_a.move({(result.amount.x + randomOffset) * -result.direction.x, 0});
                    }
                    else
                    {
                        room_a.move({0, (result.amount.y + randomOffset) * -result.direction.y});
                    }
                }
            }
        }
    }
}

void DungeonGenerator::generate_purge_bad_rooms(std::vector<Rectangle_i> &roomsOut)
{
    size_t current = 0;
    for (auto it = roomsOut.begin(); it != roomsOut.end();)
    {
        Rectangle_i &currentRoom = *it;

        bool purge = false;
        for (size_t i = 0; i < roomsOut.size(); ++i)
        {
            if (i == current)
            {
                continue;
            }

            Rectangle_i &otherRoom = roomsOut[i];

            if (currentRoom.overlapping(otherRoom).overlapping || !m_bounds.contains(currentRoom, true))
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
