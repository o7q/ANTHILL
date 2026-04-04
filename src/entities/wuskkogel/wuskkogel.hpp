#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "assets/assets.hpp"
#include "backend/viewport/render_command.hpp"
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

    EventPool<EntityEvent> update(const EntityUpdateContext &context) override;

    std::vector<RenderCommand> render(const Camera &camera) override
    {
        std::vector<RenderCommand> commands;
        return commands;
    }

  private:
    BodyUpdateHandler m_bodyHandler;

    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;

    SpriteAnimator m_animator;
};
