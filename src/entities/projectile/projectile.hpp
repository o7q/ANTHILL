#pragma once

#include "backend/viewport/viewport.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/directional.hpp"

class Projectile : public Entity, public IDirectional
{
  public:
    Projectile(Vec2<int> pos, float angle)
    {
        m_body.setPosition(pos.x, pos.y);
        m_lookAngle = angle;
        m_body.setVelocity(std::cosf(angle), std::sinf(angle));
        m_interactionBox.getBoundingBox().setSize(3, 3);
    }

    void update(EntityUpdateContext &context) override
    {
        m_body.update(context.dt);
    }
    void render(Viewport &viewport, const Camera &camera) override
    {
        renderDebug_boundingBox(viewport, camera);
    }
};
