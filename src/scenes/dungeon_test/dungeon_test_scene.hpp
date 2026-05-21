#pragma once

#include "core/math/rectangle.hpp"
#include "scene/scene.hpp"
#include "world_dungeon/dungeon_generator.hpp"

class DungeonTestScene : public Scene
{
  public:
    DungeonTestScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    DungeonGenerator m_generator;

    GridRectangle a;
    GridRectangle b;
};
