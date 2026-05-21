#pragma once

#include "core/math/triangle.hpp"
#include "core/math/vec.hpp"
#include "scene/scene.hpp"
#include <vector>

class DungeonTestScene : public Scene
{
  public:
    DungeonTestScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    std::vector<Vec2i> m_points;
    std::vector<Triangle2f> m_triangulated;
};
