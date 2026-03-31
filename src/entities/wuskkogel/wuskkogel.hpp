#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "assets/assets.hpp"
#include "backend/viewport/viewport.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/head.hpp"
#include "entity/update_context.hpp"
#include "events/entity/entity_entity.hpp"
#include "sprite/sprite_animator.hpp"
#include "world/camera/camera.hpp"

class Wuskkogel : public Entity, public IHead
{
  public:
    Wuskkogel(uint64_t id, const Assets &assets);

    void update(const EntityUpdateContext &context) override;

    void render(Viewport &viewport, const Camera &camera) override
    {
        viewport.drawTexture(
            *m_animator.getCurrentFrame(),
            camera.worldToViewport(m_body.getPosition(), viewport));
    }

  private:
    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;

    SpriteAnimator m_animator;
};
