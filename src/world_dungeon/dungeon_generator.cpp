
#include "dungeon_generator.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/random.hpp"

DungeonGenerator::DungeonGenerator()
{
    m_bounds.setPosition({100, 80});
    m_bounds.setSize({200, 160});
}

void DungeonGenerator::generate()
{
    m_rooms.clear();
    generate_place_rooms();
    generate_fix_room_intersection();
    generate_purge_bad_rooms();
}

void DungeonGenerator::generate_place_rooms()
{
    for (int i = 0; i < m_roomCount; ++i)
    {
        Vec2i randomInitialPos = {m_bounds.getPosition().x + Math::Random::unseededRandomInt(-20, 20),
                                  m_bounds.getPosition().y + Math::Random::unseededRandomInt(-20, 20)};

        Vec2i randomSize = {Math::Random::unseededRandomInt(m_minRoomSize.x, m_maxRoomSize.x),
                            Math::Random::unseededRandomInt(m_minRoomSize.y, m_maxRoomSize.y)};

        m_rooms.push_back(Rectangle_i(randomInitialPos, randomSize));
    }
}

void DungeonGenerator::generate_fix_room_intersection()
{
    for (int i = 0; i < m_roomSeparateIterations; ++i)
    {
        for (size_t j = 0; j < m_rooms.size(); ++j)
        {
            Rectangle_i &room_a = m_rooms[j];
            for (size_t k = 0; k < m_rooms.size(); ++k)
            {
                if (j == k)
                {
                    continue;
                }

                Rectangle_i &room_b = m_rooms[k];

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

void DungeonGenerator::generate_purge_bad_rooms()
{
    size_t current = 0;
    for (auto it = m_rooms.begin(); it != m_rooms.end();)
    {
        Rectangle_i &currentRoom = *it;

        bool purge = false;
        for (size_t i = 0; i < m_rooms.size(); ++i)
        {
            if (i == current)
            {
                continue;
            }

            Rectangle_i &otherRoom = m_rooms[i];

            if (currentRoom.overlapping(otherRoom).overlapping || !m_bounds.contains(currentRoom))
            {
                purge = true;
                break;
            }
        }

        if (purge)
        {
            it = m_rooms.erase(it);
        }
        else
        {
            current++;
            it++;
        }
    }
}
