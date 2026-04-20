#pragma once

#include "backend/sprite_sheet/sprite_sheet.hpp"
#include "backend/timer/timer.hpp"
#include <optional>

class SpriteAnimator
{
  public:
    SpriteAnimator(const SpriteSheet &spriteSheet)
        : r_spriteSheet(spriteSheet), m_frames(spriteSheet.getSpriteCount())
    {
        m_timer.setMode(Timer::Mode::Repeat);
    }

    void update(float dt)
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

    void setFPS(unsigned int fps) { m_timer.setDurationInSeconds(1.0f / fps); }

    void enableLooping() { m_loop = true; }
    void disableLooping() { m_loop = false; }

    void restart()
    {
        m_timer.restart();
        seek(0);
    }
    void stop()
    {
        m_timer.stop();
        seek(0);
    }
    void seek(unsigned int frame) { m_currentFrame = frame; }

    const Texture *getCurrentFrame() const { return getFrame(m_currentFrame); }
    const Texture *getFrame(unsigned int frame) const
    {
        return r_spriteSheet.getSprite(frame);
    }

    void setOrigin(std::pair<std::optional<int>, std::optional<int>> origin)
    {
        m_origin = origin;
    }

    std::pair<std::optional<int>, std::optional<int>> getOrigin() const
    {
        return m_origin;
    }

    bool completed() const { return m_timer.completed(); }

  private:
    const SpriteSheet &r_spriteSheet;
    const unsigned int m_frames = 0;

    Timer m_timer;
    unsigned int m_currentFrame = 0;
    bool m_loop = true;

    std::pair<std::optional<int>, std::optional<int>> m_origin;
};
