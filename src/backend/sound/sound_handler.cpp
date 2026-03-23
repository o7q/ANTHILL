#include "sound_handler.hpp"

#include "backend/logger/logger.hpp"

SoundHandler::SoundHandler()
{
    if (ma_engine_init(NULL, &m_engine) != MA_SUCCESS)
    {
        Logger::error("AudioSystem::AudioSystem()",
                      "Failed to initialize the miniaudio engine!");
        return;
    }

    m_initialized = true;
}
SoundHandler::~SoundHandler()
{
    ma_engine_uninit(&m_engine);
    stopAllSounds();
}

void SoundHandler::playSound(const Sound &s, const SoundPlaySettings &settings)
{
    if (!m_initialized || s.getData() == nullptr)
    {
        return;
    }

    ma_audio_buffer_config bufferConfig = ma_audio_buffer_config_init(
        s.getFormat(), s.getChannels(), s.getFrameCount(), s.getData(), NULL);

    SoundInstance instance;
    instance.buffer = (ma_audio_buffer *)malloc(sizeof(ma_audio_buffer));
    instance.sound = (ma_sound *)malloc(sizeof(ma_sound));
    m_instancePool.push_back(instance);

    ma_audio_buffer_init(&bufferConfig, instance.buffer);

    ma_sound_init_from_data_source(&m_engine, instance.buffer, 0, NULL,
                                   instance.sound);

    ma_sound_set_pitch(instance.sound, settings.pitch);
    ma_sound_start(instance.sound);
}

void SoundHandler::stopAllSounds()
{
    for (SoundInstance &instance : m_instancePool)
    {
        destroy_instance(instance);
    }

    m_instancePool.clear();
}

void SoundHandler::destroy_instance(SoundInstance &instance)
{
    if (instance.sound)
    {
        ma_sound_stop(instance.sound);
        ma_sound_uninit(instance.sound);
        free(instance.sound);
        instance.sound = nullptr;
    }
    if (instance.buffer)
    {
        ma_audio_buffer_uninit(instance.buffer);
        free(instance.buffer);
        instance.buffer = nullptr;
    }
}
