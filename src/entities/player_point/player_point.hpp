#pragma once

#include "core/viewport/render_command.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/metadata.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include <vector>

class PlayerPoint : public Entity
{
  public:
    PlayerPoint(Vec2i pos) : m_bodyHandler(m_body, m_boundingBox)
    {
        m_body.setPosition(pos);
        m_boundingBox.setSize({4, 4});
        m_metadata.type = EntityType::Collectible;
    }

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
    {
        m_bodyHandler.update(context);
    }

    void render(const Camera &camera, std::vector<RenderCommand> &commandsOut)
    {
        RectangleRenderCommandData data;
        data.a     = camera.cameraToViewport(m_body.getPosition() + m_boundingBox.getA());
        data.b     = camera.cameraToViewport(m_body.getPosition() + m_boundingBox.getB());
        data.color = Color(31, 255, 191);
        data.fill  = true;
        commandsOut.push_back({3, data});
    }

  private:
    BodyUpdateHandler m_bodyHandler;
};
