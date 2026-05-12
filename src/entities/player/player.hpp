#pragma once

#include "assets/assets.hpp"
#include "core/input/input_handler.hpp"
#include "core/math/angle.hpp"
#include "core/math/rectangle.hpp"
#include "core/viewport/render_command.hpp"
#include "entities/player/dash/player_dash.hpp"
#include "entities/player/gun/player_gun.hpp"
#include "entities/player/jetpack/player_jetpack.hpp"
#include "entities/player/sound/player_sound.hpp"
#include "entities/player/sprite/player_sprite.hpp"
#include "entity/body_update_handler/body_update_handler.hpp"
#include "entity/entity.hpp"
#include "entity/jump_handler/jump_handler.hpp"

class Player : public Entity
{
  public:
    Player(InputHandler &input, const Assets &assets);
    virtual ~Player() = default;

    void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) override;
    void render(const Camera &camera, std::vector<RenderCommand> &commandsOut) override;

    void updateAimPosition(Vec2i aimPos)
    {
        m_aimPos = aimPos;
        m_angle  = Math::Angles::vectorsToAngle((m_body.getPosition() + m_relativeHeadPosition).toFloat(),
                                                aimPos.toFloat());
    }

    virtual void damage(DamageSource source) override
    {
        // i-frames
        if (m_dash.getState() == PlayerDash::State::Dashing)
        {
            return;
        }

        m_health -= source.amount;
    }

  private:
    void update_movement_and_jump(const EntityUpdateContext &context);

  private:
    InputHandler &r_input;
    const Assets &r_assets;
    BodyUpdateHandler m_bodyHandler;
    JumpHandler m_jumpHandler;

    PlayerSprite m_sprite;
    PlayerSound m_sound;
    PlayerGun m_gun;
    PlayerDash m_dash;

    Vec2i m_aimPos;
    Angle m_angle;
    Vec2i m_relativeHeadPosition = {0, -6};

    std::optional<PositionalGridRectangle> m_dashTarget;
};
