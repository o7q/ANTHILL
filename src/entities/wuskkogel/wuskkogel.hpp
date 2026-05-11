#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "assets/assets.hpp"
#include "core/viewport/render_command.hpp"
#include "entities/wuskkogel/ai/state_machine.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "events/event_pool.hpp"
#include "sprite/sprite_animator.hpp"

class Wuskkogel : public Entity
{
  public:
    Wuskkogel(const Assets &assets, uint64_t id = 0);

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera, std::vector<RenderCommand> &commandsOut) override
    {
        // DEBUG_renderAISightPoints(m_aiPerception, camera, commandsOut);
        // DEBUG_renderAINavigation(m_aiNavigation, camera, commandsOut);

        TextureRenderCommandData data;
        data.texture  = m_animator.getCurrentFrame();
        data.position = camera.cameraToViewport(m_body.getPosition());
        data.flipX    = m_body.getVelocity().x < 0;

        commandsOut.push_back({1, data});
    }

    void damage(DamageSource source) override { m_damageSources.push_back(source); }

  private:
    BodyUpdateHandler m_bodyHandler;

    SpriteAnimator m_animator;

    WuskkogelStateMachine m_stateMachine;
    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;

    float m_lookAngle = 0.0f;
    Vec2i m_headPos   = {0, -5};

    std::vector<DamageSource> m_damageSources;
};
