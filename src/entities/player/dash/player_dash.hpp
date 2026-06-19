#pragma once

#include "px/timer/timer.hpp"
#include "entity/update_context.hpp"
#include <unordered_map>

class PlayerDash
{
  public:
    enum class State
    {
        Idle,
        Dashing
    };

    enum class Direction
    {
        Up,
        Down,
        Left,
        Right,

        UpLeft,
        UpRight,
        DownLeft,
        DownRight
    };

  public:
    PlayerDash();

    void dash(Direction direction);
    void stop() { m_state = State::Idle; }

    void update(const EntityUpdateContext &context);

    State getState() const { return m_state; }
    Vec2f getDashVelocity() const { return m_dashVelocity; }

  private:
    State m_state = State::Idle;
    Vec2f m_dashVelocity;

    Timer m_dashTimer;

    Direction m_currentDirection = Direction::Left;

    static inline const std::unordered_map<Direction, Vec2i> m_directions = {
        {Direction::Up, Vec2i{0, -1}},       {Direction::Down, Vec2i{0, 1}},
        {Direction::Left, Vec2i{-1, 0}},     {Direction::Right, Vec2i{1, 0}},
        {Direction::UpLeft, Vec2i{-1, -1}},  {Direction::UpRight, Vec2i{1, -1}},
        {Direction::DownLeft, Vec2i{-1, 1}}, {Direction::DownRight, Vec2i{1, 1}}};
};
