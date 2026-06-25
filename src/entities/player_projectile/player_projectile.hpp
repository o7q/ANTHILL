#pragma once

#include "entity/entity.hpp"
#include "entity/metadata.hpp"
#include "px/basic_types/angle.hpp"
#include "px/window/draw_types.hpp"

class PlayerProjectile : public Entity
{
  public:
    PlayerProjectile(uint64_t parent, px::Vec2i startPos, px::Angle_f startAngle, float speed)
        : Entity(parent)
    {
        m_body.setPosition(startPos);
        m_constantVelocity =
            px::Vec2f{std::cosf(startAngle.radians()), std::sinf(startAngle.radians())} * speed;

        m_collider.addRect({}, {3, 3});

        m_metadata.name = "Player Projectile";
        m_metadata.type = EntityType::Projectile;
    }

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera, std::vector<px::DrawCommand> &commandsOut) override
    {
        px::PointsDrawConfig data;
        data.points = {camera.cameraToRenderer(m_body.getPosition())};
        data.color  = px::Color(71, 255, 212);

        commandsOut.push_back({1, data});
    }

  private:
    px::Vec2f m_constantVelocity;
};
