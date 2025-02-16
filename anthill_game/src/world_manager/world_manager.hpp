#pragma once

#include <vector>

#include "../world/world.hpp"
#include "../engine/window/window.hpp"

class WorldManager
{
public:
    WorldManager(Window &window, int partiton_width, int partiton_height);
    ~WorldManager();

    void update(Vec2<float> player_position);

    const std::vector<World *> &getWorldPartitions() const { return m_world_partitons; }

private:
    void delete_world(World *world);

private:
    int max_level = 0;
    bool played_past_start = false;

    Vec2<int> m_partition_size;

    Window &m_window;

    std::vector<World *> m_world_partitons;
};