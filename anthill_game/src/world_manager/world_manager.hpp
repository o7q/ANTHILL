#pragma once

#include <vector>

#include "../engine/window/window.hpp"

#include "../world/world.hpp"
#include "../world_generator/world_generator.hpp"

class WorldManager
{
public:
    WorldManager(Window &window) : m_window(window)
    {
    }

    ~WorldManager()
    {
        purge();
    }

    void purge()
    {
        for (World *world : m_worlds)
        {
            if (world != nullptr)
            {
                delete world;
            }
        }
    }

    void update(Vec2<float> player_position)
    {
    }

    void next()
    {
        if (m_world_queue.empty())
        {
            return;
        }

        World *new_world = WorldGenerator::generate(m_window.getSDLRenderer(), m_world_queue[0]);
        pop_s_world_queue();

        new_world->setPosition(0, vertical_px_index);
        vertical_px_index += new_world->getSize().y;

        m_worlds.push_back(new_world);

        if (index > 0)
        {
        }

        ++index;
    }

    void queueNextGenerator(WorldGenerator::Settings settings)
    {
        m_world_queue.push_back(settings);
    }

    const std::vector<World *> &getWorlds() const { return m_worlds; }

private:
    void pop_s_world_queue()
    {
        m_world_queue.erase(m_world_queue.begin());
    }

private:
    Window &m_window;

    int index = 0;
    int vertical_px_index = 0;

    std::vector<World *> m_worlds;
    std::vector<WorldGenerator::Settings> m_world_queue;
};