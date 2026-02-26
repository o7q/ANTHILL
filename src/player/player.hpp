#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/entity.hpp"
#include "utils/render.hpp"

class Player : public Entity
{
  public:
    Player() { m_collisionBox.setSize(Vec2<float>(10, 20)); }

    void update() override {}

    void render(Viewport &viewport, const Camera &camera) override
    {
        Vec2<float> pos = m_verletBody.getPosition();

        Vec2<float> a = m_collisionBox.getA() + pos;
        Vec2<float> b = m_collisionBox.getB() + pos;

        a = camera.worldToViewport(a.x, a.y);
        b = camera.worldToViewport(b.x, b.y) - 1;

        Utils::Render::drawRectOutline(viewport, Vec2<int>(a.x, a.y),
                                       Vec2<int>(b.x, b.y), Color(0, 255, 100));
    }
};
