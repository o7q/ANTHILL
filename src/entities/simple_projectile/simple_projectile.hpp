#pragma once

#include "backend/viewport/viewport.hpp"
#include "debug/renderers.hpp"
#include "entity/entity.hpp"
#include "events/entity/entity_entity.hpp"

class SimpleProjectile : public Entity
{
  public:
    SimpleProjectile(uint64_t id, uint64_t parent, Vec2i startPos,
                     float startAngle, float speed)
        : Entity(id, parent)
    {
        m_body.setPosition(startPos);
        m_constantVelocity =
            Vec2f(std::cosf(startAngle), std::sinf(startAngle)) * speed;

        m_boundingBox.setSize({3, 3});

        m_metadata.name = "Projectile";
    }

    virtual void update(const EntityUpdateContext &context) override;
    void render(Viewport &viewport, const Camera &camera) override
    {
        DEBUG_renderBoundingBox(viewport, camera, m_body.getPosition(), m_boundingBox);
    }

  private:
    Vec2f m_constantVelocity;
};
