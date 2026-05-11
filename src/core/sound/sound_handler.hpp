#pragma once

#include "core/math/vec.hpp"
#include "core/sound/sound.hpp"
#include "core/time/time_handler.hpp"
#include <miniaudio/miniaudio.h>
#include <vector>

struct SoundPlaySettings
{
    float volume = 1.0f;
    float pitch  = 1.0f;
    Vec2f position;
};

class SoundHandler
{
  private:
    struct SoundInstance
    {
        SoundPlaySettings settings;
        ma_audio_buffer *buffer = nullptr;
        ma_sound *sound         = nullptr;
    };

  public:
    SoundHandler();
    SoundHandler(const SoundHandler &other)            = delete;
    SoundHandler &operator=(const SoundHandler &other) = delete;
    ~SoundHandler();

    void update(TimeHandler::Info time);
    void playSound(const Sound &s, const SoundPlaySettings settings = SoundPlaySettings());
    void stopAllSounds();

  private:
    void destroy_instance(SoundInstance &instance);

  private:
    ma_engine m_engine;
    bool m_initialized = false;

    std::vector<SoundInstance> m_instancePool;
};
