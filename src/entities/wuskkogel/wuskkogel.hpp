#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "ai/state/state.hpp"
#include "assets/assets.hpp"
#include "backend/viewport/render_command.hpp"
#include "debug/renderers.hpp"
#include "entities/wuskkogel/states/states.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/update_context.hpp"
#include "events/entity/entity_entity.hpp"
#include "events/event_pool.hpp"
#include "sprite/sprite_animator.hpp"

class Wuskkogel : public Entity
{
  public:
    Wuskkogel(uint64_t id, const Assets &assets);

    void update(const EntityUpdateContext &context,
                EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera,
                std::vector<RenderCommand> &commandsOut) override
    {
        TextureRenderCommandData data;
        data.texture = m_animator.getCurrentFrame();
        data.position = camera.cameraToViewport(m_body.getPosition());
        data.flipX = m_body.getVelocity().x < 0;

        commandsOut.push_back({1, data});

        // DEBUG_renderAISightPoints(m_aiPerception, camera, commandsOut);
    }

  private:
    void update_state(const EntityUpdateContext &context,
                      EventPool<EntityEvent> &eventsOut);

  private:
    BodyUpdateHandler m_bodyHandler;

    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;

    SpriteAnimator m_animator;

    std::unique_ptr<State<WuskkogelStateID>> m_currentState;
    uint64_t m_targetID = 0;

    float m_lookAngle = 0.0f;
    Vec2i m_headPos = {0, -5};
};
