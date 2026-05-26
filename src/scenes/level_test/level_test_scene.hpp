#pragma once

#include "core/data_structures/node_graph.hpp"
#include "scene/scene.hpp"
#include "world_generator/level_generator/room.hpp"

class LevelTestScene : public Scene
{
  public:
    LevelTestScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    NodeGraph<Room> m_roomGraph;
};
