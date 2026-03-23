#pragma once

#include "backend/sound/sound.hpp"
#include <miniaudio/miniaudio.h>
#include <vector>

struct SoundPlaySettings
{
    float pitch = 1.0f;
};

class SoundHandler
{
  private:
    struct SoundInstance
    {
        ma_audio_buffer *buffer = nullptr;
        ma_sound *sound = nullptr;
    };

  public:
    SoundHandler();
    SoundHandler(const SoundHandler &other) = delete;
    SoundHandler &operator=(const SoundHandler &other) = delete;
    ~SoundHandler();

    void playSound(const Sound &s, const SoundPlaySettings &settings);
    void stopAllSounds();

  private:
    void destroy_instance(SoundInstance &instance);

  private:
    ma_engine m_engine;
    bool m_initialized = false;

    std::vector<SoundInstance> m_instancePool;
};
