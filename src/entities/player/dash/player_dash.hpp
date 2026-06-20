#pragma once

#include "entity/update_context.hpp"
#include "px/timer/timer.hpp"
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
    px::Vec2f getDashVelocity() const { return m_dashVelocity; }

  private:
    State m_state = State::Idle;
    px::Vec2f m_dashVelocity;

    px::Timer m_dashTimer;

    Direction m_currentDirection = Direction::Left;

    static inline const std::unordered_map<Direction, px::Vec2i> m_directions = {
        {Direction::Up, px::Vec2i{0, -1}},       {Direction::Down, px::Vec2i{0, 1}},
        {Direction::Left, px::Vec2i{-1, 0}},     {Direction::Right, px::Vec2i{1, 0}},
        {Direction::UpLeft, px::Vec2i{-1, -1}},  {Direction::UpRight, px::Vec2i{1, -1}},
        {Direction::DownLeft, px::Vec2i{-1, 1}}, {Direction::DownRight, px::Vec2i{1, 1}}};
};
