#pragma once

#include "core/sprite_sheet/sprite_sheet.hpp"
#include "core/timer/timer.hpp"

class SpriteAnimator
{
  public:
    SpriteAnimator(const SpriteSheet &spriteSheet, int fps = 10);

    void update(float dt);

    void restart();
    void stop();

    void setFPS(unsigned int fps) { m_timer.setDurationInSeconds(1.0f / fps); }

    void enableLooping() { m_loop = true; }
    void disableLooping() { m_loop = false; }

    void seek(unsigned int frame) { m_currentFrame = frame; }

    const Texture *getCurrentFrame() const { return getFrame(m_currentFrame); }
    const Texture *getFrame(unsigned int frame) const { return r_spriteSheet.getSprite(frame); }
    int getCurrentFrameIndex() const { return m_currentFrame; }

  private:
    const SpriteSheet &r_spriteSheet;
    const unsigned int m_frames = 0;

    Timer m_timer;
    unsigned int m_currentFrame = 0;
    bool m_loop                 = true;
};
