#pragma once

#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/metadata.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include "px/window/draw_types.hpp"
#include <vector>

class PlayerPoint : public Entity
{
  public:
    PlayerPoint(px::Vec2i pos) : m_bodyHandler(m_body, m_collider)
    {
        m_body.setPosition(pos);
        m_collider.addRect({}, {4, 4});
        m_collider.addRect({}, {10, 10});
        m_metadata.type = EntityType::Energy;
    }

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
    {
        m_bodyHandler.update(context);
    }

    void render(const Camera &camera, std::vector<px::DrawCommand> &commandsOut)
    {
        px::RectangleDrawConfig data;
        data.rectangle = m_collider.getPrimary();
        data.rectangle.setPosition(camera.cameraToRenderer(m_body.getPosition()));
        data.color = px::Color(31, 255, 191);
        data.fill  = true;
        commandsOut.push_back({3, data});
    }

  private:
    BodyUpdateHandler m_bodyHandler;
};
