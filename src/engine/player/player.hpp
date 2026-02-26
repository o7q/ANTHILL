#pragma once

#include "engine/backend/viewport.hpp"
#include "engine/camera.hpp"
#include "engine/entity/entity.hpp"

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
        b = camera.worldToViewport(b.x, b.y);

        viewport.drawRectOutline(Vec2<int>(a.x, a.y), Vec2<int>(b.x, b.y),
                                 Color(0, 255, 100));
    }
};
