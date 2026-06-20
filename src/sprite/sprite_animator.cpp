#include "sprite_animator.hpp"

SpriteAnimator::SpriteAnimator(const px::SpriteSheet &spriteSheet, int fps)
    : r_spriteSheet(spriteSheet), m_frames(spriteSheet.getSpriteCount())
{
    m_timer.setMode(px::Timer::Mode::Repeat);
    setFPS(fps);
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
