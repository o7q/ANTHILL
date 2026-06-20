#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "assets/assets.hpp"
#include "entities/player_point/player_point.hpp"
#include "entities/wuskkogel/ai/state_machine.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"
#include "events/entity/events.hpp"
#include "events/event_pool.hpp"
#include "px/window/render_command.hpp"
#include "sprite/sprite_animator.hpp"
#include <memory>

class Wuskkogel : public Entity
{
  public:
    Wuskkogel(const Assets &assets, uint64_t id = 0);

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) override;

    void render(const Camera &camera, std::vector<px::RenderCommand> &commandsOut) override
    {
        px::TextureRenderCommandData data;
        data.texture  = m_animator.getCurrentFrame();
        data.position = camera.cameraToRenderer(m_body.getPosition());
        data.flipX    = m_body.getVelocity().x < 0;

        commandsOut.push_back({1, data});
    }

    void damage(DamageSource source) override { m_damageSources.push_back(source); }

    void onKill(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) const override
    {
        auto playerPoint = std::make_unique<PlayerPoint>(m_body.getPosition());
        eventsOut.emit(std::make_unique<EntitySpawnEvent>(context.id, std::move(playerPoint)));
    }

  private:
    BodyUpdateHandler m_bodyHandler;

    SpriteAnimator m_animator;

    WuskkogelStateMachine m_stateMachine;
    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;

    float m_lookAngle   = 0.0f;
    px::Vec2i m_headPos = {0, -5};

    std::vector<DamageSource> m_damageSources;

    px::Timer m_idleSoundTimer;
};
