#pragma once

#include "backend/viewport/render_command.hpp"
#include "entity/entity.hpp"
#include "events/entity/entity_entity.hpp"

class SimpleProjectile : public Entity
{
  public:
    SimpleProjectile(uint64_t parent, Vec2i startPos, float startAngle,
                     float speed)
        : Entity(parent)
    {
        m_body.setPosition(startPos);
        m_constantVelocity =
            Vec2f(std::cosf(startAngle), std::sinf(startAngle)) * speed;

        m_boundingBox.setSize({3, 3});

        m_metadata.name = "Projectile";
    }

    void update(const EntityWorldContext &worldContext,
                EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera,
                std::vector<RenderCommand> &commandsOut) override
    {
        PointsRenderCommandData data;
        data.points = {camera.cameraToViewport(m_body.getPosition())};
        data.color = Color(232, 147, 28);

        commandsOut.push_back({1, data});
    }

  private:
    Vec2f m_constantVelocity;
};
