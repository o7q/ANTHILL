#pragma once

#include <vector>

#include "../world/world.hpp"
#include "../engine/window/window.hpp"

class WorldManager
{
public:
    WorldManager(Window &window, int width, int height);
    ~WorldManager();

    void update(Vec2<float> player_position);

    const std::vector<World *> &getWorlds() const { return m_worlds; }

private:
    void delete_world(World *world);

private:
    int max_level = 0;
    bool played_past_start = false;

    Vec2<int> m_world_size;

    Window &m_window;

    std::vector<World *> m_worlds;
};