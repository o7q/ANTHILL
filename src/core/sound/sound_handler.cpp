#include "sound_handler.hpp"

#include "core/logger/logger.hpp"
#include "core/sound/sound.hpp"

SoundHandler::SoundHandler()
{
    if (ma_engine_init(NULL, &m_engine) != MA_SUCCESS)
    {
        Logger::error("AudioSystem::AudioSystem()", "Failed to initialize the miniaudio engine!");
        return;
    }

    m_initialized = true;
}
SoundHandler::~SoundHandler()
{
    stopAllSounds();
    if (m_initialized)
    {
        ma_engine_uninit(&m_engine);
    }
}

void SoundHandler::update(TimeHandler::Info time)
{
    for (auto it = m_instancePool.begin(); it != m_instancePool.end();)
    {
        if (it->sound)
        {
            ma_sound_set_pitch(it->sound, it->settings.pitch * time.speed_multiplier);
        }

        if (!it->buffer || !it->sound || ma_sound_at_end(it->sound))
        {
            destroy_instance(*it);
            it = m_instancePool.erase(it);
        }
        else
        {
            it++;
        }
    }
}

void SoundHandler::playSound(const Sound &s, const SoundPlaySettings settings)
{
    if (!m_initialized || s.getData() == nullptr)
    {
        return;
    }

    SoundInstance instance;
    instance.settings = settings;
    instance.buffer   = (ma_audio_buffer *)malloc(sizeof(ma_audio_buffer));
    instance.sound    = (ma_sound *)malloc(sizeof(ma_sound));

    ma_audio_buffer_config bufferConfig =
        ma_audio_buffer_config_init(s.getFormat(), s.getChannels(), s.getFrameCount(), s.getData(), NULL);

    if (ma_audio_buffer_init(&bufferConfig, instance.buffer) != MA_SUCCESS)
    {
        free(instance.buffer);
        free(instance.sound);
        return;
    }

    if (ma_sound_init_from_data_source(&m_engine, instance.buffer, 0, NULL, instance.sound) != MA_SUCCESS)
    {
        ma_audio_buffer_uninit(instance.buffer);
        free(instance.buffer);
        free(instance.sound);
        return;
    }

    ma_sound_set_volume(instance.sound, settings.volume);
    ma_sound_set_pitch(instance.sound, settings.pitch);
    ma_sound_set_position(instance.sound, settings.position.x, settings.position.y, -1);
    ma_sound_start(instance.sound);

    m_instancePool.push_back(instance);
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
