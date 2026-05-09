#pragma once

#include "assets/assets.hpp"
#include "camera/camera.hpp"
#include "core/viewport/render_command.hpp"
#include "entities/player/dash/player_dash.hpp"
#include "entity/body/entity_body.hpp"
#include "sprite/sprite_system.hpp"

class PlayerSprite
{
  public:
    enum class State
    {
        None,
        Idle,
        Run
    };

    enum class HeadAnimation
    {
        Idle,
        IdleUp45,
        IdleDown45,

        Run,
        RunUp45,
        RunDown45
    };

    enum class TorsoAnimation
    {
        Idle,
        Run
    };

    enum class LegsAnimation
    {
        Idle,
        Run
    };

    struct UpdateData
    {
        const EntityBody &body;
        const PlayerDash &dash;
        float lookAngle = 0.0f;
    };

  public:
    PlayerSprite(const Assets &assets);

    void update(UpdateData data, float dt);
    void render(Vec2i pos, Vec2i aimPos, const Camera &camera, std::vector<RenderCommand> &commandsOut);

  private:
    State determine_state(const EntityBody &body);

    void update_head(State state, float lookAngle, float dt);
    void update_torso(State state, float dt);
    void update_legs(State state, float dt);

    void init_head(const Assets &assets);
    void init_torso(const Assets &assets);
    void init_legs(const Assets &assets);

  private:
    SpriteSystem<HeadAnimation> m_head;
    SpriteSystem<TorsoAnimation> m_torso;
    SpriteSystem<LegsAnimation> m_legs;

    State m_lastState = State::None;
};
