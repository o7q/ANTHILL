#pragma once

#include "core/math/angle.hpp"
#include "core/viewport/render_command.hpp"
#include "entity/entity.hpp"
#include "entity/metadata.hpp"

class PlayerProjectile : public Entity
{
  public:
    PlayerProjectile(uint64_t parent, Vec2i startPos, Angle startAngle, float speed) : Entity(parent)
    {
        m_body.setPosition(startPos);
        m_constantVelocity = Vec2f(std::cosf(startAngle.radians()), std::sinf(startAngle.radians())) * speed;

        m_collider.addRect({}, {3, 3});

        m_metadata.name = "Player Projectile";
        m_metadata.type = EntityType::Projectile;
    }

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera, std::vector<RenderCommand> &commandsOut) override
    {
        PointsRenderCommandData data;
        data.points = {camera.cameraToViewport(m_body.getPosition())};
        data.color  = Color(71, 255, 212);

        commandsOut.push_back({1, data});
    }

  private:
    Vec2f m_constantVelocity;
};
