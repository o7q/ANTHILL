#pragma once

#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/triangle.hpp"
#include "scene/scene.hpp"
#include "world_dungeon/dungeon_generator.hpp"
#include <vector>

class DungeonTestScene : public Scene
{
  public:
    DungeonTestScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    std::vector<Rectangle_i> m_rects;
    std::vector<Triangle_i> m_triangulated;
    DungeonGenerator m_generator;
};
