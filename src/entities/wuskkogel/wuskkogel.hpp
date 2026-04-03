#pragma once

#include "ai/navigation/ai_navigation.hpp"
#include "ai/perception/ai_perception.hpp"
#include "assets/assets.hpp"
#include "backend/viewport/viewport.hpp"
#include "debug/renderers.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/update_context.hpp"
#include "events/entity/entity_entity.hpp"
#include "sprite/sprite_animator.hpp"
#include "world/camera/camera.hpp"

class Wuskkogel : public Entity
{
  public:
    Wuskkogel(uint64_t id, const Assets &assets);

    void update(const EntityUpdateContext &context) override;

    void render(Viewport &viewport, const Camera &camera) override
    {
        Viewport::TextureDrawSettings settings;
        settings.pos = camera.worldToViewport(m_body.getPosition(), viewport);

        if (m_body.getVelocity().x < 0)
        {
            settings.flipX = true;
        }

        viewport.drawTexture(*m_animator.getCurrentFrame(), settings);

        DEBUG_renderAINavigationInProgress(viewport, camera, m_aiNavigation,
                                           {8, 8});
        DEBUG_renderAINavigation(viewport, camera, m_aiNavigation);
    }

  private:
    BodyUpdateHandler m_bodyHandler;

    AIPerception m_aiPerception;
    AINavigation m_aiNavigation;

    SpriteAnimator m_animator;
};
