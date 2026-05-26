#pragma once

#include "core/data_structures/node_graph.hpp"
#include "level_generator/room.hpp"
#include "scene/scene.hpp"

class LevelTestScene : public Scene
{
  public:
    LevelTestScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    NodeGraph<const Room *> m_roomGraph;
};
