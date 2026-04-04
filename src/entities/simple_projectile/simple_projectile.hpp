#pragma once

#include "backend/viewport/render_command.hpp"
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

    virtual EventPool<EntityEvent>
    update(const EntityUpdateContext &context) override;

    std::vector<RenderCommand> render(const Camera &camera) override
    {
        std::vector<RenderCommand> commands;
        return commands;
    }

  private:
    Vec2f m_constantVelocity;
};
