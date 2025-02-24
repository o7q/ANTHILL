#pragma once

#include <vector>

#include "../engine/window/window.hpp"

#include "../world/world.hpp"
#include "../world_generator/world_generator.hpp"

class WorldManager
{
public:
    WorldManager(Window &window) : m_window(window) {}

    ~WorldManager();

    void queue(WorldGenerator::Settings settings);
    void updateQueue();

    void purge();

    const std::vector<World *> &getWorlds() const { return m_worlds; }
    int getVerticalPos() const {return m_vertical_pos;}

private:
    void purge_first_world();

    float size_in_memory_mb();

private:
    Window &m_window;

    int m_index = 0;
    int m_vertical_pos = 0;

    const int m_max_memory_mb = 1000.0f;

    std::vector<World *> m_worlds;
    std::vector<WorldGenerator::ThreadSafeGenerator *> m_generator_queue;
};