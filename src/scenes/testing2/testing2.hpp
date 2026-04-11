#pragma once

#include "assets/assets.hpp"
#include "backend/texture/texture.hpp"
#include "math/vec.hpp"
#include "scene/scene.hpp"
#include "utils/data_structures/index_2d.hpp"

class TestScene2 : public Scene
{
  public:
    TestScene2(const Assets &assets, Window &window) : Scene(assets, window) {}

  protected:
    void onStart() override;
    void onTick() override;

  private:
    Texture m_screen =
        Texture({r_viewport.getSize().x, r_viewport.getSize().y});

    std::unordered_map<Index2D, Vec2f, Index2DHash> m_seeds;
};
