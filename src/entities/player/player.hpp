#pragma once

#include "assets/assets.hpp"
#include "entities/player/dash/player_dash.hpp"
#include "entities/player/gun/player_gun.hpp"
#include "entities/player/sprite/player_sprite.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/jump_handler/jump_handler.hpp"
#include "px/basic_types/angle.hpp"
#include "px/canvas/draw_types.hpp"
#include "px/input/input_handler.hpp"

class Player : public Entity
{
  public:
    Player(px::InputHandler &input, const Assets &assets);
    virtual ~Player() = default;

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) override;
    void render(const Camera &camera, std::vector<px::DrawCommand> &commandsOut) override;

    void updateAimPosition(px::Vec2i aimPos)
    {
        m_aimPos = aimPos;
        m_angle  = px::Angle((m_body.getPosition() + m_relativeHeadPosition).toFloat(), aimPos.toFloat());
    }

    void damage(DamageSource source) override
    {
        // i-frames
        if (m_dash.getState() == PlayerDash::State::Dashing)
        {
            return;
        }

        m_health -= source.amount;
    }

    int getEnergy() const { return m_energy; }

  private:
    void update_entity_interaction(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut);
    void update_movement_and_jump(const EntityUpdateContext &context);

  private:
    px::InputHandler &r_input;
    const Assets &r_assets;

    BodyUpdateHandler m_bodyHandler;
    JumpHandler m_jumpHandler;
    PlayerGun m_gun;
    PlayerDash m_dash;

    int m_energy = 0;

    px::Vec2i m_aimPos;
    px::Angle_f m_angle;
    px::Vec2i m_relativeHeadPosition = {0, -6};

    bool m_dashJumpRequested = false;

    PlayerSprite m_sprite;
};
