#pragma once

#include "backend/sprite_sheet/sprite_sheet.hpp"

class SpriteAnimator
{
  public:
    SpriteAnimator(const SpriteSheet &spriteSheet)
        : r_spriteSheet(spriteSheet), m_frames(spriteSheet.getSpriteCount())
    {
    }

    void update(float dt)
    {
        m_frameCounter += (m_fps * dt) / 60.0f;

        if (m_frameCounter >= 1.0f)
        {
            m_currentFrame = (m_currentFrame + 1) % m_frames;
            m_frameCounter = 0;
        }
    }

    void setFPS(unsigned int fps) { m_fps = fps; }

    void play() { m_playing = true; }
    void pause() { m_playing = false; }
    void stop()
    {
        pause();
        seek(0);
    }
    void seek(unsigned int frame) { m_currentFrame = frame; }

    const Texture *getCurrentFrame() const { return getFrame(m_currentFrame); }
    const Texture *getFrame(unsigned int frame) const
    {
        return r_spriteSheet.getSprite(frame);
    }

  private:
    const SpriteSheet &r_spriteSheet;
    const unsigned int m_frames = 0;

    bool m_playing = false;
    float m_frameCounter = 0;
    unsigned int m_currentFrame = 0;
    unsigned int m_fps = 20;
};
