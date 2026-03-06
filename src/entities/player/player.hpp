#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entity/entity.hpp"
#include "types/bounding_box.hpp"
#include "utils/render.hpp"

class Player : public Entity
{
  public:
    Player(World &world) : Entity(world)
    {
        m_worldCollisionHandler.getCollisionBox().setSize(20, 30);
    }
    ~Player() override {}

    void update(float dt) override
    {
        handleMotion();
        handleWorldInteractions(dt);
    }

    void render(Viewport &viewport, const Camera &camera) override
    {
        Vec2<int> pos = m_body.getPosition().toGrid();

        Vec2<int> a = m_worldCollisionHandler.getCollisionBox().getA() + pos;
        Vec2<int> b = m_worldCollisionHandler.getCollisionBox().getB() + pos;

        a = camera.worldToViewport(a.x, a.y);
        b = camera.worldToViewport(b.x, b.y);

        Utils::Render::drawRectOutline(viewport, a, b, Color(0, 255, 100));
    }
};
