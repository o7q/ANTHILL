
#include "dungeon_generator.hpp"
#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/random.hpp"

DungeonGenerator::DungeonGenerator()
{
    m_bounds.setPosition({100, 80});
    m_bounds.setSize({200, 160});
}

void DungeonGenerator::generate()
{
    m_roomGraph.clear();
    generate_place_rooms();
    generate_fix_room_intersection();
    // generate_purge_bad_rooms();
}

void DungeonGenerator::generate_place_rooms()
{
    for (int i = 0; i < m_roomCount; ++i)
    {
        Vec2i randomInitialPos = {m_bounds.getPosition().x + Math::Random::unseededRandomInt(-20, 20),
                                  m_bounds.getPosition().y + Math::Random::unseededRandomInt(-20, 20)};

        Vec2i randomSize = {Math::Random::unseededRandomInt(m_minRoomSize.x, m_maxRoomSize.x),
                            Math::Random::unseededRandomInt(m_minRoomSize.y, m_maxRoomSize.y)};

        Node<Vec2i> node;
        node.value = randomSize;

        m_roomGraph.set(randomInitialPos, node);
    }
}

void DungeonGenerator::generate_fix_room_intersection()
{
    for (int i = 0; i < m_roomSeparateIterations; ++i)
    {
        for (auto &[index_a, node_a] : m_roomGraph.getNodes())
        {
            Rectangle_i room_a(index_a, node_a.value);
            for (auto &[index_b, node_b] : m_roomGraph.getNodes())
            {
                if (index_a == index_b)
                {
                    continue;
                }

                Rectangle_i room_b(index_b, node_b.value);

                Rectangle_i::OverlapResult result = room_a.overlapping(room_b);
                if (result.overlapping)
                {
                    int randomOffset = Math::Random::unseededRandomInt(m_roomMinSpacing, m_roomMaxSpacing);
                    if (result.amount.x < result.amount.y)
                    {
                        room_a.move({(result.amount.x + randomOffset) * -result.direction.x, 0});
                        m_roomGraph.move(index_a, room_a.getPosition());
                    }
                    else
                    {
                        room_a.move({0, (result.amount.y + randomOffset) * -result.direction.y});
                        m_roomGraph.move(index_a, room_a.getPosition());
                    }
                }
            }
        }
    }
}

void DungeonGenerator::generate_purge_bad_rooms()
{
    // size_t current = 0;
    // for (auto it = m_rooms.begin(); it != m_rooms.end();)
    // {
    //     Rectangle_i &currentRoom = *it;

    //     bool purge = false;
    //     for (size_t i = 0; i < m_rooms.size(); ++i)
    //     {
    //         if (i == current)
    //         {
    //             continue;
    //         }

    //         Rectangle_i &otherRoom = m_rooms[i];

    //         if (currentRoom.overlapping(otherRoom).overlapping || !m_bounds.contains(currentRoom))
    //         {
    //             purge = true;
    //             break;
    //         }
    //     }

    //     if (purge)
    //     {
    //         it = m_rooms.erase(it);
    //     }
    //     else
    //     {
    //         current++;
    //         it++;
    //     }
    // }
}
