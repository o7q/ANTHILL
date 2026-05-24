#pragma once

#include "core/data_structures/node_graph.hpp"
#include "scene/scene.hpp"
#include "world_generator/dungeon/dungeon_generator.hpp"

class DungeonTestScene : public Scene
{
  public:
    DungeonTestScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    NodeGraph<Vec2i> m_roomGraph;
    DungeonGenerator m_generator;
};
