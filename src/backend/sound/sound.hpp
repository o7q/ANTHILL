#pragma once

#include <filesystem>
#include <miniaudio/miniaudio.h>

class Sound
{
  public:
    Sound() = default;
    Sound(const std::filesystem::path &path);
    Sound(const Sound &other) = delete;
    Sound &operator=(const Sound &other) = delete;
    ~Sound();

    ma_format getFormat() const { return m_format; }
    ma_uint64 getFrameCount() const { return m_frameCount; }
    ma_uint32 getChannels() const { return m_channels; }

    const void *getData() const { return p_data; }

  private:
    void *p_data = nullptr;
    ma_format m_format = ma_format_f32;
    ma_uint64 m_frameCount = 0;
    ma_uint32 m_channels = 0;
};
