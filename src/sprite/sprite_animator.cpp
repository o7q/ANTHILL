#include "sprite_animator.hpp"

SpriteAnimator::SpriteAnimator(const SpriteSheet &spriteSheet)
    : r_spriteSheet(spriteSheet), m_frames(spriteSheet.getSpriteCount())
{
    m_timer.setMode(Timer::Mode::Repeat);
    restart();
}
SpriteAnimator::SpriteAnimator(
    const SpriteSheet &spriteSheet, unsigned int fps,
    std::pair<std::optional<int>, std::optional<int>> origin, Vec2i offset)
    : r_spriteSheet(spriteSheet), m_frames(spriteSheet.getSpriteCount())
{
    setFPS(fps);
    setOrigin(origin);
    setOffset(offset);

    m_timer.setMode(Timer::Mode::Repeat);
    restart();
}

void SpriteAnimator::update(float dt)
{
    if (m_timer.completed())
    {
        m_currentFrame = (m_currentFrame + 1) % m_frames;

        if (m_currentFrame == 0 && !m_loop)
        {
            m_timer.stop();
        }
    }
    m_timer.update(dt);
}

void SpriteAnimator::restart()
{
    m_timer.restart();
    seek(0);
}
void SpriteAnimator::stop()
{
    m_timer.stop();
    seek(0);
}

void SpriteAnimator::transitionFrom(const SpriteAnimator &other)
{
    m_timer.setClockTime(other.getFrameSubTime());
    seek(other.getCurrentFrameIndex());
}
