#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "assets/assets.hpp"
#include "backend/timer/timer.hpp"
#include "backend/viewport/render_command.hpp"
#include "debug/renderers.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/update_context.hpp"
#include "events/entity/entity_entity.hpp"
#include "events/event_pool.hpp"
#include "sprite/sprite_animator.hpp"

class Wuskkogel : public Entity
{
  private:
    enum class State
    {
        Idle,
        Follow,
        Attack,
        Flee
    };

  public:
    Wuskkogel(uint64_t id, const Assets &assets);

    void update(const EntityUpdateContext &context,
                EventPool<EntityEvent> &eventsOut) override;

    void update_idle(const EntityUpdateContext &context,
                     EventPool<EntityEvent> &eventsOut);
    void update_follow(const EntityUpdateContext &context,
                       EventPool<EntityEvent> &eventsOut);
    void update_attack(const EntityUpdateContext &context,
                       EventPool<EntityEvent> &eventsOut);
    void update_flee(const EntityUpdateContext &context,
                     EventPool<EntityEvent> &eventsOut);

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
    BodyUpdateHandler m_bodyHandler;

    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;

    SpriteAnimator m_animator;

    State m_state = State::Idle;

    float m_lookAngle = 0.0f;
    Vec2i m_headPos= {0, -5};

    const Entity* p_target = nullptr;
    Timer m_targetLostTimer;
    Timer m_targetRecalcTimer;
};
