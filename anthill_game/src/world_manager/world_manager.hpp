#pragma once

#include <vector>

#include "../engine/window/window.hpp"

#include "../world/world.hpp"
#include "../world_generator/world_generator.hpp"

class WorldManager
{
public:
    WorldManager(Window &window) : m_window(window) {}

    ~WorldManager()
    {
        purge();
    }
    
    void generateLatest();
    void queue(WorldGenerator::Settings settings);
    
    void purge();

    const std::vector<World *> &getWorlds() const { return m_worlds; }

private:
    void purge_first_world();

    float size_in_memory_mb();

private:
    Window &m_window;

    int index = 0;
    int vertical_pos_index = 0;

    const int m_max_memory_mb = 1000.0f;

    std::vector<World *> m_worlds;
    std::vector<WorldGenerator::Settings> m_world_queue;
};