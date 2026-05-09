#include "sound.hpp"

#include "core/logger/logger.hpp"

Sound::Sound(const std::filesystem::path &path)
{
    const std::string pathString = path.string();

    ma_decoder_config decoderConfig = ma_decoder_config_init(m_format, 0, 0);
    ma_decoder decoder;
    if (ma_decoder_init_file(pathString.c_str(), &decoderConfig, &decoder) != MA_SUCCESS)
    {
        Logger::error("Sound::Sound()", "Failed to decode: " + pathString);
        return;
    }

    if (ma_decoder_get_length_in_pcm_frames(&decoder, &m_frameCount) != MA_SUCCESS)
    {
        Logger::error("Sound::Sound()", "Failed to get frame count: " + pathString);
        ma_decoder_uninit(&decoder);
        return;
    }
    m_channels = decoder.outputChannels;

    ma_uint32 bytesPerFrame = ma_get_bytes_per_frame(decoder.outputFormat, decoder.outputChannels);

    p_data = (void *)malloc(m_frameCount * bytesPerFrame);
    if (ma_decoder_read_pcm_frames(&decoder, p_data, m_frameCount, NULL) != MA_SUCCESS)
    {
        Logger::error("Sound::Sound()", "Failed to read pcm frames: " + pathString);
        if (p_data)
        {
            free(p_data);
        }
        p_data = nullptr;
        ma_decoder_uninit(&decoder);
        return;
    }

    ma_decoder_uninit(&decoder);

    Logger::info("Sound::Sound()", "Successfully loaded: " + pathString);
}
Sound::~Sound()
{
    if (p_data)
    {
        free(p_data);
    }
}
