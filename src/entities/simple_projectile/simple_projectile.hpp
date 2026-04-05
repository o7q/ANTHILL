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

    void update(const EntityUpdateContext &context,
                EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera,
                std::vector<RenderCommand> &commandsOut) override
    {
        RectangleRenderCommandData data;
        data.a = camera.cameraToViewport(m_body.getPosition() +
                                         m_boundingBox.getA());
        data.b = camera.cameraToViewport(m_body.getPosition() +
                                         m_boundingBox.getB());
        data.color = Color(255, 0, 0);

        RenderCommand command;
        command.data = data;

        commandsOut.push_back(command);
    }

  private:
    Vec2f m_constantVelocity;
};
