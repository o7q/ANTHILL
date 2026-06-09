#pragma once

#include "core/data_structures/node_graph.hpp"
#include "room/room.hpp"
#include "scene/scene.hpp"

class LevelTestScene : public Scene
{
  public:
    LevelTestScene(Window &window) : Scene(window) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    Room m_testRoom1 = Room({10, 10});
    Room m_testRoom2 = Room({20, 20});
    Room m_testRoom3 = Room({70, 70});
    NodeGraph<const Room *> m_roomGraph;
};
