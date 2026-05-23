#pragma once

#include "core/data_structures/node_graph.hpp"
#include "core/math/color.hpp"
#include "scene/scene.hpp"

class DungeonTestScene : public Scene
{
  public:
    DungeonTestScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    NodeGraph<Color> m_triangulationGraph;
    NodeGraph<Color> m_minimumTreeGraph;
};
