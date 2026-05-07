#pragma once

#include "assets/assets.hpp"
#include "backend/input/input_handler.hpp"
#include "backend/viewport/render_command.hpp"
#include "entities/player/dash/dash_handler.hpp"
#include "entities/player/sprite/player_sprite.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/jump_handler/jump_handler.hpp"
#include "item/inventory.hpp"
#include "math/angle.hpp"
#include "math/rectangle.hpp"

class Player : public Entity
{
  public:
    Player(uint64_t id, InputHandler &input, const Assets &assets);
    virtual ~Player() = default;

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) override;
    void render(const Camera &camera, std::vector<RenderCommand> &commandsOut) override;

    void updateAimPosition(Vec2i aimPos)
    {
        m_aimPos = aimPos;
        m_angle  = Math::Angles::vectorsToAngle((m_body.getPosition() + m_relativeHeadPosition).toFloat(),
                                                aimPos.toFloat())
                       .degrees();
    }

    virtual void damage(DamageSource source) override
    {
        // i-frames
        if (m_dashHandler.getState() == DashHandler::State::Dashing)
        {
            return;
        }

        m_health -= source.amount;
    }

  private:
    void update_movement_and_jump(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut);
    void update_items(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut);

  private:
    InputHandler &r_input;
    const Assets &r_assets;
    BodyUpdateHandler m_bodyHandler;
    PlayerSprite m_sprite;

    Inventory m_inventory;

    JumpHandler m_jumpHandler;
    DashHandler m_dashHandler;

    Vec2i m_aimPos;
    float m_angle                = 0.0f;
    Vec2i m_relativeHeadPosition = {0, -6};
    std::vector<PositionalGridRectangle> m_highlightRects;
};
